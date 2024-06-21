package cz.cvut.kuznear1.dogapp.core.data.db

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import cz.cvut.kuznear1.dogapp.features.breed.data.db.BreedDao
import cz.cvut.kuznear1.dogapp.features.breed.data.db.DbBreed

@Database(version = 1, entities = [DbBreed::class])
abstract class DogDatabase : RoomDatabase() {

    abstract fun breedDao(): BreedDao

    companion object {

        fun newInstance(context: Context): DogDatabase {
            return Room.databaseBuilder(context, DogDatabase::class.java, "dog.db").build()
        }
    }
}