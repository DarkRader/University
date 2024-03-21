package fit.bikot.expression

sealed interface Expr {
    val value: Int
    val pri: Int
    fun accept(v : Visitor)
    companion object {
        val ZER0 = Lit(0)
        val ONE = Lit(1)
        val TWO = Lit(2)
    }
}

enum class Op(val symbol: String, val pri: Int) {
    PLS("+", 3), MNS("-", 3), MLT("*", 2), DIV("/", 2)

}

data class Lit(override val value: Int) : Expr {
    //   override fun toString() = "$value"
    override val pri: Int = 0
    override fun accept(v : Visitor) {
        v.visit(this)
    }

}

data class UnOp(val op: Op, val oprnd: Expr) : Expr {
    override val value: Int
        get() = when (op) {
            Op.PLS -> oprnd.value
            Op.MNS -> -oprnd.value
            else -> error("invalid expr")
        }
    override val pri: Int = 1
    //    override fun toString() = "${op.symbol}${oprnd.value}"
    override fun accept(v : Visitor) {
        v.visit(this)
    }
}

data class BinOp(val op: Op, val le: Expr, val re: Expr) : Expr {
    override val value: Int
        get() = when (op) {
            Op.PLS -> le.value + re.value
            Op.MNS -> le.value - re.value
            Op.MLT -> le.value * re.value
            Op.DIV -> le.value / re.value
        }
    override val pri = op.pri

    private fun inclose(s: String, w: Boolean) =
        if (w) "(${s})"
        else s

    /*    override fun toString(): String {
            val ls = inclose(le.toString(), le.pri > op.pri)
            val rs = inclose(re.toString(), re.pri > op.pri)
            return "${ls} ${op.symbol} ${rs}"
        }*/
    override fun accept(v : Visitor) {
        v.visit(this)
    }
}

val memory = mutableMapOf("x" to 0, "y" to 0)


fun main() {
    val e1 = Lit(3)
    val e2 = Lit(4)
    val e3 = UnOp(Op.MNS, e1)
    println(e1 == e2)
    println(e1)
    println(e3.value)
    //println(e3)
    val e4 = BinOp(Op.PLS, e1, e1)
    // println(e4)
    val e5 = e4.copy(le = e2)
    // println(e5)
    val e6 = BinOp(Op.MLT, e4, Lit(2))
    // println("${e6} = ${e6.value}")
    listOf(e1, e3, e4, e5, e6).forEach { println("${it} = ${it.value}") }
    val pv = PostFix()
    e6.accept(pv)
    println(pv.buffer)

}
