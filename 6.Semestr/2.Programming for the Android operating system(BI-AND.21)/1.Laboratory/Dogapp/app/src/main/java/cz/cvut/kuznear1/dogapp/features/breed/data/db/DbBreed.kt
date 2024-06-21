package cz.cvut.kuznear1.dogapp.features.breed.data.db

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "breed")
data class DbBreed(
    @PrimaryKey val id: String,
    val name: String,
    val description: String,
)