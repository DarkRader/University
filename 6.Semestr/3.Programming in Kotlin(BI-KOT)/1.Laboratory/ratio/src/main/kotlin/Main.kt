package fit.bikot.ratio

import java.util.logging.Logger


class Ratio(_nom: Int, _denom: Int) {

    val nom: Int
    val denom: Int

    constructor(_nom: Int) : this(_nom, 1)

    init {
        require(_denom != 0)
        val gcd = gcd(_nom, _denom)
        nom = _nom / gcd
        denom = _denom / gcd
    }

    override fun toString() = "$nom/$denom"

    companion object {
        fun gcd(n: Int, d: Int): Int =
            if (d == 0) n
            else gcd(d, n % d)
    }

    override fun equals(other: Any?): Boolean =
        if (this === other) true
        else if (other !is Ratio) false
        else this.let { it.denom == other.denom && it.nom == other.nom }

    override fun hashCode(): Int = nom xor denom

    operator fun times(ro: Ratio) = Ratio(nom * ro.nom, denom * ro.denom)

    operator fun times(ro: Int) = this * Ratio(ro)

    val inv : Ratio by lazy {
        Logger.getAnonymousLogger().info("inv")
        Ratio(denom, nom)
    }

    operator fun div(ro: Ratio) = this * ro.inv

    operator fun div(ro: Int) = this.inv * ro
}

operator fun Int.times(ro: Ratio) = ro * this

operator fun String.unaryPlus(): Ratio {
    val nd = this.split("/")
    return try {
        Ratio(nd[0].toInt(), nd[1].toInt())
    } catch (ex: NumberFormatException) {
        error("Invalid format: ${ex.message}")
    }
}

fun main() {
    val r1 = Ratio(1, 2)
    val r2 = Ratio(2, 4)
    listOf(
        Ratio(1, 2),
        Ratio(2, 4),
        r1 * r2,
        r1 * 3,
        3 * r1,
       r1 / r2,
        r1 / 3,
        +"2/4",
        +"3/2"
    ).forEach(::println)
    println(r1 == r2)

}