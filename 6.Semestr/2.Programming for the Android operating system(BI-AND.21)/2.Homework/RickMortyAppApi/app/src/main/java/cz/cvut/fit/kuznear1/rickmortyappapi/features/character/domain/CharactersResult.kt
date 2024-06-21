package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain

data class CharactersResult(
    val characters: List<Character>,
    val isSuccess: Boolean,
)

data class CharacterResult(
    val character: Character?,
    val isSuccess: Boolean,
)