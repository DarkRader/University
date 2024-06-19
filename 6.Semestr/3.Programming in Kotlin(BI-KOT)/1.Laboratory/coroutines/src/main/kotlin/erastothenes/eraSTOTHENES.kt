package erastothenes

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.channels.ReceiveChannel
import kotlinx.coroutines.channels.produce
import kotlinx.coroutines.delay
import kotlinx.coroutines.runBlocking

fun CoroutineScope.natural(): ReceiveChannel<Int> = produce {
    var i = 2
    while (true)
        send(i++)
}

fun CoroutineScope.filterMlt(n: Int, rch: ReceiveChannel<Int>):                                              ReceiveChannel<Int> =
    produce {
        while (true) {
            val x: Int = rch.receive()
            if (x % n != 0)
                send(x)
        }
    }

fun CoroutineScope.prime(): ReceiveChannel<Int> {
    return produce  {
        var ch= natural()
        while (true) {
            val p = ch.receive()
            ch = filterMlt(p, ch)
            send(p)
        }
    }

}

fun main() {
    runBlocking {
        val nch = natural()
        val fc = filterMlt(3, nch)
        val pch = prime()
        while (true) {
            delay(300)
            println(pch.receive())
        }

    }


}