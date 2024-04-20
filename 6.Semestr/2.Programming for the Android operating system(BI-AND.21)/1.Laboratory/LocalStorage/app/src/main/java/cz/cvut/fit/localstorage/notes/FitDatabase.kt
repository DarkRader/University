package cz.cvut.fit.localstorage.notes

import androidx.room.AutoMigration
import androidx.room.Database
import androidx.room.RoomDatabase

@Database(
    version = 3,
    entities = [Note::class],
    autoMigrations = [
        AutoMigration(2, 3)
    ]
)
abstract class FitDatabase : RoomDatabase() {

    abstract fun noteDao(): NoteDao
}
