package cz.cvut.fit.kuznear1.rickmortyappapi.core.data.db

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.db.CharacterDao
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.db.DbCharacter

@Database(version = 1, entities = [DbCharacter::class])
abstract class RickAndMortyDatabase : RoomDatabase() {

    abstract fun characterDao(): CharacterDao

    companion object {

        fun newInstance(context: Context): RickAndMortyDatabase {
            return Room.databaseBuilder(context, RickAndMortyDatabase::class.java, "rick.db").build()
        }
    }

}