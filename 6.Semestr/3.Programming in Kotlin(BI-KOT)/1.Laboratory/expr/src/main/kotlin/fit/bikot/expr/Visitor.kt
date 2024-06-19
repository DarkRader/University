package fit.bikot.expr

interface Visitor {
    fun visit(il : Lit)
    fun visit(il : UnOp)
    fun visit(il : BinOp)
    fun visit(il : Var)
}

class PostFix : Visitor {
    val buffer  = StringBuilder()
    override fun visit(il: Lit)  {
        buffer.append("${il} ")
    }

    override fun visit(il: UnOp) {
        il.oprnd.accept(this)
        buffer.append(" ${il.op.symbol}")
    }

    override fun visit(il: BinOp) {
        il.le.accept(this)
        il.re.accept(this)
        buffer.append("${il.op.symbol} ")
    }

    override fun visit(il: Var) {
        buffer.append("${il} ")
    }

}