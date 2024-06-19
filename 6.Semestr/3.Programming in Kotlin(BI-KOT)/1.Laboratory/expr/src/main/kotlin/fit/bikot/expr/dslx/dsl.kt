package fit.bikot.expr.dslx

import fit.bikot.expr.*
import java.util.*


fun Queue<Expr>.genbinop(binop: Op, block: Queue<Expr>.() -> Unit): Expr {
    /*    val cont = ArrayDeque<Expr>()
        cont.block()
        check(cont.size==2)
        val result = BinOp(binop, cont.poll(), cont.poll())
        add(result)
        return result*/
    val x: Expr =
        ArrayDeque<Expr>()
            .apply {
                block()
                check(size == 2)
            }
            .let { BinOp(binop, poll(), poll()) }
            .also { add(it) }
    return x
}

fun Queue<Expr>.genunop(unop: Op, block: Queue<Expr>.() -> Unit): Expr {
    val cont = ArrayDeque<Expr>()
    cont.block()
    check(cont.size == 1)
    val result = UnOp(unop, cont.poll())
    add(result)
    return result
}

fun Queue<Expr>.pls(block: Queue<Expr>.() -> Unit): Expr = genbinop(Op.PLS, block)
fun Queue<Expr>.mns(block: Queue<Expr>.() -> Unit): Expr = genbinop(Op.PLS, block)


fun Queue<Expr>.lit(value: Int) {
    add(Lit(value))
}

fun main() {
    val e = ArrayDeque<Expr>().pls {
        lit(2)
        lit(3)
    }
    println(e)

}