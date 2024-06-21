package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.api

import kotlinx.serialization.Serializable

@Serializable
data class CharactersResponse(
    val info: ApiCharacter.Info,
    val results: List<ApiCharacter.Character>
)
