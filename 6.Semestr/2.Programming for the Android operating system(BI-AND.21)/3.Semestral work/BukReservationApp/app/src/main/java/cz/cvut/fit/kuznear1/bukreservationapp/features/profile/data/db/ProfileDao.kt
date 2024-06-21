package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.db

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface ProfileDao {
    @Query("SELECT * FROM user")
    suspend fun getAllUsers(): List<DbUser>

    @Query("SELECT * FROM user WHERE username = :id")
    suspend fun getUser(id: String): DbUser?

    @Insert
    suspend fun insert(calendar: DbUser)

    @Query("DELETE FROM user")
    suspend fun deleteAll()


}