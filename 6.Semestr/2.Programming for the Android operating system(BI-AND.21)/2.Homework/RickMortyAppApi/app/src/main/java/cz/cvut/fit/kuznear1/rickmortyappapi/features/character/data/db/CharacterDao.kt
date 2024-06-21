package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.db

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface CharacterDao {

    @Query("SELECT * FROM character")
    fun getCharacterStream(): Flow<List<DbCharacter>>

    @Query("SELECT * FROM character")
    suspend fun getAllCharacters(): List<DbCharacter>

    @Query("SELECT * FROM character WHERE id = :id")
    suspend fun getCharacter(id: Int): DbCharacter?

    @Insert
    suspend fun insert(characters: List<DbCharacter>)

    @Query("DELETE FROM character")
    suspend fun deleteAll()

    @Query("UPDATE character SET favourite = :isFavorite WHERE id = :id")
    suspend fun updateCharacterFavorite(id: Int, isFavorite: Boolean)

}