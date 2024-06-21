package cz.cvut.fit.kuznear1.rickmortyapp.model

import cz.cvut.fit.kuznear1.rickmortyapp.R

data class Character(
    val id: Int,
    val icon: Int,
    val name: String,
    val status: String,
    val species: String,
    val type: String,
    val gender: String,
    val origin: String,
    val location: String,
    var favourite: Boolean,
)

val characters = listOf(
    Character(
        1,
        R.drawable.rick,
        "Rick Sancgez",
        "Alive",
        "Human",
        "-",
        "Male",
        "Earth (C-137)",
        "Earth (Replacement Dimension)",
        false
    ),
    Character(
        2,
        R.drawable.`morty`,
        "Morty Smith",
        "Alive",
        "Human",
        "-",
        "Male",
        "Earth (C-137)",
        "Earth (Replacement Dimension)",
        false
    ),
    Character(
        3,
        R.drawable.summer,
        "Summer Smith",
        "Alive",
        "Human",
        "-",
        "Female",
        "Earth (C-137)",
        "Earth (Replacement Dimension)",
        false
    ),
    Character(
        4,
        R.drawable.beth,
        "Beth Smith",
        "Alive",
        "Human",
        "-",
        "Female",
        "Earth (C-137)",
        "Earth (Replacement Dimension)",
        false
    ),
    Character(
        5,
        R.drawable.jerry,
        "Jerry Smith",
        "Alive",
        "Human",
        "-",
        "Male",
        "Earth (C-137)",
        "Earth (Replacement Dimension)",
        false
    ),
    Character(
        6,
        R.drawable.abadango_cluster_princess,
        "Abadango Cluster Princess",
        "Alive",
        "Alien",
        "-",
        "Female",
        "Abadango",
        "Abadango",
        false
    ),
    Character(
        7,
        R.drawable.abradolf_lincler,
        "Abradolf Lincler",
        "Unknown",
        "Human",
        "Genetic experiment",
        "Male",
        "Earth (Replacement Dimension)",
        "Testicle Monster Dimension",
        false
    ),
    Character(
        8,
        R.drawable.adjudicator_rick,
        "Adjudicator Rick",
        "Dead",
        "Human",
        "-",
        "Female",
        "Unknown",
        "Citadel of Ricks",
        false
    ),
    Character(
        9,
        R.drawable.agency_director,
        "Agency Director",
        "Dead",
        "Human",
        "-",
        "Female",
        "Earth (Replacement Dimension)",
        "Earth (Replacement Dimension)",
        false
    ),
    Character(
        10,
        R.drawable.alan_rails,
        "Alan Rails",
        "Dead",
        "Human",
        "Superhuman (Ghost trains summoner)",
        "Male",
        "Unknown",
        "Worldender's lair",
        false
    ),
    Character(
        11,
        R.drawable.albert_einstein,
        "Albert Einstein",
        "Dead",
        "Human",
        "-",
        "Male",
        "Earth (C-137)",
        "Earth (Replacement Dimension)",
        false
    ),
    Character(
        12,
        R.drawable.alexander,
        "Alexander",
        "Dead",
        "Human",
        "-",
        "Male",
        "Earth (C-137)",
        "Anatomy Park",
        false
    ),
    Character(
        13,
        R.drawable.alien_googah,
        "Alien Googah",
        "Unknown",
        "Alien",
        "-",
        "Unknown",
        "Unknown",
        "Earth (Replacement Dimension)",
        false
    ),
    Character(
        14,
        R.drawable.alien_morty,
        "Alien Morty",
        "Unknown",
        "Alien",
        "-",
        "Male",
        "Unknown",
        "Citadel of Ricks",
        false
    ),
    Character(
        15,
        R.drawable.alien_rick,
        "Alien Rick",
        "Unknown",
        "Alien",
        "-",
        "Male",
        "Unknown",
        "Citadel of Ricks",
        false
    ),
)