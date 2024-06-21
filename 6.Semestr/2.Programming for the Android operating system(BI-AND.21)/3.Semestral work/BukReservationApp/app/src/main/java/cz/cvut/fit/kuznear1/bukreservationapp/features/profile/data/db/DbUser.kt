package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.db

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "user")
data class DbUser(
    @PrimaryKey
    val username: String
)