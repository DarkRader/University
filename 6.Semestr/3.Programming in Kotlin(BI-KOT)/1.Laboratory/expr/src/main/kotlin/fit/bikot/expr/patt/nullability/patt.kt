package fit.bikot.expr.patt.nullability

import fit.bikot.expr.*
import fit.bikot.expr.Expr.Companion.ONE
import fit.bikot.expr.Expr.Companion.TWO
import fit.bikot.expr.Expr.Companion.ZER0

interface ExprPatt {
    fun match(e: Expr): Boolean
    fun matchn(e: Expr): Expr? {
        return if (match(e)) e else null
    }
}

object UnivPatt : ExprPatt {
    override fun match(e: Expr) = true
}

open class UOpPattCls(vararg val ops: Op = Op.values(), val oprndPatt: ExprPatt = UnivPatt) : ExprPatt {
    override fun match(e: Expr) = e is UnOp && e.op in ops && oprndPatt.match(e.oprnd)
    override fun matchn(e: Expr): UnOp? {
        return super.matchn(e) as? UnOp
    }
}

open class BOpPattCls(
    vararg val ops: Op = Op.values(), val loprndPatt: ExprPatt = UnivPatt,
    val roprndPatt: ExprPatt = UnivPatt
) : ExprPatt {
    override fun match(e: Expr) = e is BinOp && e.op in ops
            && loprndPatt.match(e.le)
            && roprndPatt.match(e.re)

    override fun matchn(e: Expr): BinOp? {
        return super.matchn(e) as? BinOp
    }
}

open class LitPattCls(val range: IntRange = Int.MIN_VALUE..Int.MAX_VALUE) : ExprPatt {
    override fun match(e: Expr) = e is Lit && e.value in range
    override fun matchn(e: Expr): Lit? {
        return super.matchn(e) as? Lit
    }
}

object BopPatt : BOpPattCls()

object BopLitLitPatt : BOpPattCls(loprndPatt = LitPatt, roprndPatt = LitPatt)

object BopPlsLZeroPatt : BOpPattCls(ops = arrayOf(Op.PLS, Op.MNS),  loprndPatt = ZeroPatt)

object BopLRZeroPatt : BOpPattCls(loprndPatt = ZeroPatt)

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

fun Expr.optimn(): Expr {
    val opt =
        UnPlsPatt.matchn(this)?.oprnd ?:
        UMnsLitPatt.matchn(this)?.oprnd?.let { Lit(-it.value) } ?:
        BopLitLitPatt.matchn(this)?.let { Lit(it.value) }?:
        BopPlsLZeroPatt.matchn(this)?.re?:
        UnivPatt.matchn(
            this
        ) ?: error("fail")

    /*        UMnsLitPatt.match(this) -> Lit(-(this as UnOp).oprnd.value)
            BopLitLitPatt.match(this) -> Lit((this as BinOp).value)
            BopPatt.match(this) -> (this as BinOp).copy(le = le.optim(), re = re.optim())
            UnivPatt.match(this) -> this
            else -> error("fail")*/

    return if (opt != this) opt.optimn()
    else opt
}


fun main() {
    listOf(
        Lit(1),
        UnOp(Op.PLS, TWO),
        UnOp(Op.MNS, TWO),
        BinOp(Op.PLS, ONE, TWO),
        BinOp(Op.PLS, ZER0, Var("x"))
/*

        UnOp(PLS, UnOp(PLS, TWO)),
        UnOp(MNS, TWO),
        BinOp(PLS, ONE, UnOp(PLS, TWO)),
        BinOp(MLT, TWO, TWO)*/
    ).forEach {
        println("$it  ------------- ${it.optimn()}")
    }

}