package fit.bikot.expr.dslx.mapping

import fit.bikot.expr.BinOp
import fit.bikot.expr.Expr
import fit.bikot.expr.Lit
import fit.bikot.expr.Op

val Int.toExpr: Expr
    get() = Lit(this)

fun Expr.binop(op: Op, ro: Int): Expr = BinOp(op, this, Lit(ro))

fun Expr.binop(op: Op, ro: Expr): Expr = BinOp(op, this, ro)

fun Int.binop(op: Op, ro: Expr): Expr = BinOp(op, Lit(this), ro)

operator fun Expr.plus(ro: Int) = binop(Op.PLS, ro)
operator fun Expr.plus(ro: Expr) = binop(Op.PLS, ro)
operator fun Int.plus(ro: Expr) = binop(Op.PLS, ro)

operator fun Expr.times(ro: Int) = binop(Op.MLT, ro)
operator fun Expr.times(ro: Expr) = binop(Op.MLT, ro)

operator fun Int.times(ro: Expr) = binop(Op.MLT, ro)

operator fun Int.not(): Expr = Lit(this)

fun main() {
    val e: Expr = 1.toExpr
    val e2: Expr = !1
    val e3 = !1 + 2
    val e4 = !1 + !2
    listOf(
        e, e2, e3, e4,
        1 + 2 * !3,
        (!1 + 2) * 3
    ).forEach(::println)
}