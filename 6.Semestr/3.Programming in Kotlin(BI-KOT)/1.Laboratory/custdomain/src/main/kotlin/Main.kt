package fit.bikot.ratio

data class Cust(val id: Long, val name: String)

interface CustDAO {
    val all: List<Cust>
    fun create(name: String)
    fun delete(id: Long)
    fun get(id: Long): Cust?
}

object CustDAOMap : CustDAO {
    val custs = mutableMapOf(1L to Cust(1L, "Tom"))
    override val all: List<Cust>
        get() = custs.values.toList()

    override fun create(name: String) {
        val id = (custs.values.map(Cust::id).maxOrNull() ?: 0) + 1
        val c =  Cust(id, name)
        custs[c.id,] = c
    }

    override fun delete(id: Long) {
        custs.remove(id)
    }

    override fun get(id: Long): Cust? =
        custs[id]

}

val custFacade: CustDAO by lazy {
    CustDAOMap
}

fun main() {
    println("Hello World!")
}