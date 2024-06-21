package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.db

import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map

class CharacterLocalDataSource(private val characterDao: CharacterDao) {

    fun getCharacterStream(): Flow<List<Character>> = characterDao.getCharacterStream().map { dbCharacters ->
        dbCharacters.map { it.toDomain() }
    }

    private fun DbCharacter.toDomain(): Character {
        return Character(
            id = id,
            name = name,
            status = status,
            species = species,
            type = type,
            gender = gender,
            origin = origin,
            location = location,
            favourite = favourite,
            imageUrl = imageUrl,
        )
    }

    suspend fun getAllCharacters(): List<Character> {
        val dbCharacters = characterDao.getAllCharacters()
        return dbCharacters.map { it.toDomain() }
    }

    suspend fun getCharacter(id: Int): Character? = characterDao.getCharacter(id)?.toDomain()

    suspend fun insert(characters: List<Character>) {
        val dbCharacter = characters.map { character ->
            DbCharacter(
                id = character.id,
                name = character.name,
                status = character.status,
                species = character.species,
                type = character.type,
                gender = character.gender,
                origin = character.origin,
                location = character.location,
                favourite = character.favourite,
                imageUrl = character.imageUrl,
            )
        }
        characterDao.insert(dbCharacter)
    }

    suspend fun updateCharacterFavorite(id: Int, isFavorite: Boolean) {
        characterDao.updateCharacterFavorite(id, isFavorite)
    }

    suspend fun deleteAll() {
        characterDao.deleteAll()
    }
}