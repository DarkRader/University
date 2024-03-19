package fit.bikot.expression

interface Visitor {
    fun visit(il : Lit)
    fun visit(il : UnOp)
    fun visit(il : BinOp)
}

class PostFix : Visitor {
    val buffer  = StringBuilder()
    override fun visit(il: Lit)  {
        buffer.append("${il} ")
    }

    override fun visit(il: UnOp) {
        il.e.accept(this)
        buffer.append(" ${il.op.symbol}")
    }

    override fun visit(il: BinOp) {
        il.le.accept(this)
        il.re.accept(this)
        buffer.append("${il.op.symbol} ")
    }

}
