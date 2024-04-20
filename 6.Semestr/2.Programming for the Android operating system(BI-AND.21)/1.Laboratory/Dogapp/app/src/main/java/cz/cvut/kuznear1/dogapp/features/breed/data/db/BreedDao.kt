package cz.cvut.kuznear1.dogapp.features.breed.data.db

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface BreedDao {

    @Query("SELECT * FROM breed")
    fun getBreedsStream(): Flow<List<DbBreed>>

    @Query("SELECT * FROM breed WHERE id = :id")
    suspend fun getBreed(id: String): DbBreed?

    @Insert
    suspend fun insert(breeds: List<DbBreed>)

    @Query("DELETE FROM breed")
    suspend fun deleteAll()
}
