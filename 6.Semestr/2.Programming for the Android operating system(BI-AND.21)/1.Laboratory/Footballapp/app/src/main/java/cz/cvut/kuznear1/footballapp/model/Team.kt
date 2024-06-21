package cz.cvut.kuznear1.footballapp.model

data class Team(
    val id: Int,
    val name: String,
    val logoUrl: String,
    val points: Int,
)

val teams = listOf(
    Team(1, "Chelsea", "https://upload.wikimedia.org/wikipedia/en/thumb/c/cc/Chelsea_FC.svg/1200px-Chelsea_FC.svg.png", 10),
    Team(2, "Barcelona", "https://upload.wikimedia.org/wikipedia/en/thumb/4/47/FC_Barcelona_%28crest%29.svg/2020px-FC_Barcelona_%28crest%29.svg.png", 10),
    Team(3, "Sparta", "https://upload.wikimedia.org/wikipedia/commons/thumb/d/dd/AC-Sparta-LOGO2021.svg/1200px-AC-Sparta-LOGO2021.svg.png", 10),
    Team(4, "Slavia", "https://www.designportal.cz/wp-content/uploads/2022/07/slavia-logo-touch_branding-01.jpg", 10),
    )