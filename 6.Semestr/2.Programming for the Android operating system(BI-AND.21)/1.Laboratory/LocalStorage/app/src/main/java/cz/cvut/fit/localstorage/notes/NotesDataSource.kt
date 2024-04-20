package cz.cvut.fit.localstorage.notes

import androidx.room.Room
import androidx.room.migration.Migration
import androidx.sqlite.db.SupportSQLiteDatabase
import cz.cvut.fit.localstorage.appContext
import kotlinx.coroutines.flow.Flow

object NotesDataSource {

    private val database = Room.databaseBuilder(
        context = appContext,
        klass = FitDatabase::class.java,
        name = "fit_database"
    ).addMigrations(
        object: Migration(1, 2) {
            override fun migrate(db: SupportSQLiteDatabase) {
                db.execSQL("ALTER TABLE note_db ADD title TEXT NOT NULL DEFAULT ''")
            }
        }
    ).build()

    private val noteDao = database.noteDao()

    suspend fun insert(note: Note) {
        noteDao.insert(note)
    }

    fun getAllStream(): Flow<List<Note>> {
        return noteDao.getAllStream()
    }

    suspend fun delete(note: Note) {
        noteDao.delete(note)
    }

    suspend fun update(note: Note) {
        noteDao.update(note)
    }

    suspend fun deleteAll() {
        noteDao.deleteAll()
    }
}
