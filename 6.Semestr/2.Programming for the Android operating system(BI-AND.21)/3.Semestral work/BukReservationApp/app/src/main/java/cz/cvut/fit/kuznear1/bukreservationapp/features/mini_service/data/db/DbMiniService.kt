package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.db

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "mini_service")
data class DbMiniService(
    @PrimaryKey
    val uuid: String,
    val name: String,
    val service_alias: String
)
