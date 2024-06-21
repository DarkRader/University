package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data

import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.api.CharacterRemoteDataSource
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.db.CharacterLocalDataSource
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.CharacterResult
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.CharactersResult
import kotlinx.coroutines.flow.first

class CharacterRepository(
    private val localDataSource: CharacterLocalDataSource,
    private val remoteDataSource: CharacterRemoteDataSource,
) {

    suspend fun getCharacters(): CharactersResult {
        return try {
            val characters = remoteDataSource.getCharacters()
            localDataSource.deleteAll()
            localDataSource.insert(characters)
            CharactersResult(characters, isSuccess = true)
        } catch (t: Throwable) {
            CharactersResult(localDataSource.getCharacterStream().first(), isSuccess = false)
        }
    }

    suspend fun getAllCharacters() = localDataSource.getAllCharacters()

    suspend fun getCharacter(id: Int) = localDataSource.getCharacter(id)

    suspend fun changeCharacterFavourite(id: Int, favourite: Boolean) = localDataSource.updateCharacterFavorite(id, favourite)

    suspend fun getFilteredCharacters(name: String): CharactersResult {
        return try {
            val characters = remoteDataSource.getFilteredCharacters(name)
            CharactersResult(characters, isSuccess = true)
        } catch (t: Throwable) {
            CharactersResult(localDataSource.getCharacterStream().first(), isSuccess = false)
        }
    }

    suspend fun getCharacterApi(id: Int): CharacterResult {
      return try {
          val character = remoteDataSource.getCharacter(id)
          CharacterResult(character, isSuccess = true)
      } catch (t: Throwable) {
          CharacterResult(null, isSuccess = false)
      }
    }
}
