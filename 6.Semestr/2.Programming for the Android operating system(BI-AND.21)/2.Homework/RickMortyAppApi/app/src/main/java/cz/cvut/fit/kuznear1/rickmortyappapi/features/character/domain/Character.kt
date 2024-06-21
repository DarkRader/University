package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain

data class Character(
    val id: Int,
    val name: String,
    val status: String,
    val species: String,
    val type: String?,
    val gender: String,
    val origin: String,
    val location: String,
    var favourite: Boolean,
    val imageUrl: String,
)