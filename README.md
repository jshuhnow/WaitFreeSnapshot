## Wait-free Atomic Snapshot

### Algorithm
In a parallel environment, the element can be modified during collecting snapshot. Hence, we need to scrutinize that the acquired snapshot is clean or not(or dirty).

Here are the basic idea of `scan()`.

<pre>
oldCopy = collect()
while(true) {
    newCopy = collect()
    if (oldCopy == newCopy) return oldCopy
    // TODO :: return WAIT-FREE snapshot, which means you have to escape this loop in bounded-time
}
</pre>

It will be done with *N* repetitions by checking `moved[i]`. It records which threads have been observed to move in the `scan()`.

To record that the other thread changed the value,

<pre>
// In update()
a_table[threadId].stamp++
</pre>

This will make the `line 4` of `scan()`, `oldCopy == newCopy` not hold.

<pre>
moved[] = {false, }
oldCopy = collect()
while(true) {
    newCopy = collect()
    if (oldCopy == newCopy) return oldCopy
    for (j) {
        if (oldCopy[j] != newCopy[j]) {
            if (moved[j]) return oldCopy.snap
            else { 
                moved[j] = true
                oldCopy = newCopy
                continue while
            }
        }
    }
} 
</pre>

We check `moved[j]` is true and if so, just return the collected snap. This always returns clean snapshot because we can guarantee that the second change means the snap taken was not interleaved.

### Implementation
We use naive c pointers to record or process the arrays to avoid memory leaking.

#### How to check total count

<pre>
volatile int status;
enum status_t {PENDING,RUNNING,END};
std::mutex lk; // this should be used only for evaluating performance
</pre>

`status` is declared as `volatile int` to prevent the following codes being optimized.

<pre>
void Manager::run(int tid) {
    int localUpdate = 0;
    while(status==PENDING); // spinlock
    while(status==RUNNING) {
        snapshot.update(tid, localUpdate);
        ++localUpdate;
    }
    {
        std::unique_lock<std::mutex> lock(lk);
        totalUpdate += localUpdate;
    }
}
</pre>

The status will be changed at here.

<pre>
for (std::size_t i=0; i < threadCount; i++)
    threads[i] = std::thread(&Manager::run, this, i);
status = RUNNING;
__sync_synchronize();

std::this_thread::sleep_for(std::chrono::seconds(RUNNING_TIME));
__sync_synchronize();
status = END;
</pre>


### Performance
CPU - Intel(R) Xeon(R) CPU E5-2697 v2 @ 2.70GHz (24 core)  
RAM - 256GB  
OS - Ubuntu 16. 04. 3 LTS  
![performance](/performance.png)
