package queue_test

import (
    "dbms-go/queue"
    "testing"
)

func BenchmarkQueuePush(b *testing.B) {
    for i := 0; i < b.N; i++ {
        q := queue.NewQueue(1002)
        for j := 0; j < 1000; j++ {
            q.Push("x")
        }
    }
}

func BenchmarkQueuePop(b *testing.B) {
    q := queue.NewQueue(1000)
    
    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        if q.Head == q.Tail {
            for j := 0; j < 100; j++ {
                q.Push("x")
            }
        }
        q.Pop()
    }
}
