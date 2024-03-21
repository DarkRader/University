package fit.bikot.exprpatt.patt

import fit.bikot.expression.*
import fit.bikot.expression.Expr.Companion.ONE
import fit.bikot.expression.Expr.Companion.TWO


interface ExprPatt {
    fun match(e: Expr): Boolean
}

object UnivPatt : ExprPatt {
    override fun match(e: Expr) = true
}

open class UOpPattCls(vararg val ops: Op = Op.values(), val oprndPatt: ExprPatt = UnivPatt) : ExprPatt {
    override fun match(e: Expr) = e is UnOp && e.op in ops && oprndPatt.match(e.oprnd)
}

open class BOpPattCls(
    vararg val ops: Op = Op.values(), val loprndPatt: ExprPatt = UnivPatt,
    val roprndPatt: ExprPatt = UnivPatt
) : ExprPatt {
    override fun match(e: Expr) = e is BinOp && e.op in ops
            && loprndPatt.match(e.le)
            && roprndPatt.match(e.re)
}

open class LitPattCls(val range: IntRange = Int.MIN_VALUE..Int.MAX_VALUE) : ExprPatt {
    override fun match(e: Expr) = e is Lit && e.value in range
}

object BopPatt : BOpPattCls()

object BopLitLitPatt : BOpPattCls(loprndPatt = LitPatt, roprndPatt = LitPatt)

object LitPatt : LitPattCls()

object ZeroPatt : LitPattCls(0..0)
object OnePatt : LitPattCls(1..1)

object UnPlsPatt : UOpPattCls(Op.PLS)

object UMnsLitPatt : UOpPattCls(Op.MNS, oprndPatt = LitPatt)


fun Expr.optim(): Expr {
    val opt = when {
        UnPlsPatt.match(this) -> (this as UnOp).oprnd
        UMnsLitPatt.match(this) -> Lit(-(this as UnOp).oprnd.value)
        BopLitLitPatt.match(this) -> Lit((this as BinOp).value)
        BopPatt.match(this) -> (this as BinOp).copy(le = le.optim(), re = re.optim())
        UnivPatt.match(this) -> this
        else -> error("fail")
    }
    return if (opt != this) opt.optim()
    else opt
}

fun main() {
    listOf(
        Lit(1),
        UnOp(Op.PLS, TWO),
        UnOp(Op.PLS, UnOp(Op.PLS, TWO)),
        UnOp(Op.MNS, TWO),
        BinOp(Op.PLS, ONE, UnOp(Op.PLS, TWO)),
        BinOp(Op.MLT, TWO, TWO)
    ).forEach {
        println("$it  ------------- ${it.optim()}")
    }

}
