package fit.bikot.helloworld

data class Person(val name: String, val age: Int)

/*
{

    override fun toString()= "Person($name, $age)"
    override fun equals(other: Any?)=
        if (other == null) false
        else if (other !is Person) false
        else name == other.name && age == other.age

    override fun hashCode() = name.hashCode() xor age.hashCode()

}
*/

fun main() {
    val tom = Person("Tom", 22)
    val tom2 = Person("Tom", 22)
    println(tom)
    println(tom == tom2)
    println(tom === tom2)

}