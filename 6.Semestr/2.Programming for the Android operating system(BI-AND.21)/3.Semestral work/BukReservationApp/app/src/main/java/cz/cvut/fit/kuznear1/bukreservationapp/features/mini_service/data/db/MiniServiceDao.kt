package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.db

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface MiniServiceDao {

    @Query("SELECT * FROM mini_service")
    fun getMiniServicesStream(): Flow<List<DbMiniService>>

    @Query("SELECT * FROM mini_service")
    suspend fun getAllMiniServices(): List<DbMiniService>

    @Query("SELECT * FROM mini_service WHERE uuid = :id")
    suspend fun getMiniService(id: String): DbMiniService?

    @Insert
    suspend fun insertAll(miniServices: List<DbMiniService>)

    @Insert
    suspend fun insert(miniService: DbMiniService)

    @Query("DELETE FROM mini_service WHERE uuid = :id")
    suspend fun deleteMiniServiceById(id: String)

    @Query("DELETE FROM mini_service")
    suspend fun deleteAll()
}