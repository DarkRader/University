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
        "Earth (Replacement Dimension)"
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
        "Earth (Replacement Dimension)"
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
        "Earth (Replacement Dimension)"
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
        "Earth (Replacement Dimension)"
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
        "Earth (Replacement Dimension)"
    )
)