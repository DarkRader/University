package cz.cvut.fit.localstorage.notes

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.Query
import androidx.room.Update
import kotlinx.coroutines.flow.Flow

@Dao
interface NoteDao {

    @Insert
    suspend fun insert(note: Note)

    @Query("SELECT * FROM note_db")
    fun getAllStream(): Flow<List<Note>>

    @Delete
    suspend fun delete(note: Note)

    @Update
    suspend fun update(note: Note)

    @Query("DELETE FROM note_db")
    suspend fun deleteAll()
}
