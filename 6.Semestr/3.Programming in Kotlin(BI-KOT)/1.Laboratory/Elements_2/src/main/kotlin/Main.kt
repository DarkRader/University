package fit.bikot.elements

interface Elem {
    val content: List<String>
    val w: Int
        get() = if (content.isEmpty()) 0
        else content.first().length //  content.first()?.length?:0
    val h: Int
        get() = content.size

    fun create(content: List<String>): Elem
    infix fun above(that: Elem): Elem {
        require(this.w == that.w)
        return create(this.content + that.content)
    }

    infix fun beside(that: Elem): Elem {
        require(this.h == that.h)
        return create(content.zip(that.content).map { it.first + it.second })
    }
}
/*

fun Elem.widenL(nw : Int) : Elem {

}
*/

abstract class AElem : Elem {
    override fun toString() = content.joinToString(separator = "\n")
}


open class BasicElem(override val content: List<String>) : AElem() {
    init {
        if (content.isNotEmpty()) {
            val w = content.first().length
            require(content.all { w == it.length }) { "fail" }
        }
    }

    override fun create(content: List<String>) = BasicElem(content)
}
open class CharElem(c: Char, w: Int, h: Int) : BasicElem(List(h){ c.toString().repeat(w) })

fun main() {
    val e = BasicElem(listOf("Hel", "Wrd"))
    val e2 = BasicElem(listOf("xyz", "abc"))
    println(e above e2)
    println(e beside e2)
    println(CharElem('*', 5, 8))
}
