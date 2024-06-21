package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.api

import android.content.Context
import coil.ImageLoader
import coil.request.ImageRequest
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character

class CharacterRemoteDataSource(
    private val apiDescription: CharacterApiDescription,
    private val context: Context,
) {

    suspend fun getCharacter(id: Int): Character {
        val character = mapApiCharacter(apiDescription.getCharacter(id))

        fetchSingleCharacterImage(character)

        return character
    }

    suspend fun getFilteredCharacters(name: String): List<Character> {
        val characters = apiDescription.getFilteredCharacters(name).results.map { apiCharacter ->
            mapApiCharacter(apiCharacter)
        }

        return fetchCharactersImage(characters)
    }
    suspend fun getCharacters(): List<Character> {
        val characters = apiDescription.getCharacters().results.map { apiCharacter ->
            mapApiCharacter(apiCharacter)
        }

        return fetchCharactersImage(characters)
    }

    private fun mapApiCharacter(apiCharacter: ApiCharacter.Character): Character {
        return Character(
            id = apiCharacter.id,
            name = apiCharacter.name,
            status = apiCharacter.status,
            species = apiCharacter.species,
            type = apiCharacter.type,
            gender = apiCharacter.gender,
            origin = apiCharacter.origin.name,
            location = apiCharacter.location.name,
            favourite = false,
            imageUrl = apiCharacter.image,
        )
    }

    private fun fetchCharactersImage(characters: List<Character>): List<Character> {
        characters.forEach { character ->
            fetchSingleCharacterImage(character)
        }
        return characters
    }

    private fun fetchSingleCharacterImage(character: Character): Character {
        val imageLoader = ImageLoader.Builder(context)
            .build()

        val request = ImageRequest.Builder(context)
            .data(character.imageUrl)
            .target { drawable ->

            }
            .build()

        imageLoader.enqueue(request)

        return character
    }
}