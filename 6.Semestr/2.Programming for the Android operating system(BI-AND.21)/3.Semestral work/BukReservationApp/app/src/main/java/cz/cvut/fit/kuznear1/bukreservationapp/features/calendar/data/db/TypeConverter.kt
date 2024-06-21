package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.db

import androidx.room.TypeConverter
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api.ApiCalendar
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json

class Converters {
    @TypeConverter
    fun fromStringList(value: String?): List<String>? {
        return value?.split(",")
    }

    @TypeConverter
    fun fromListString(list: List<String>?): String? {
        return list?.joinToString(",")
    }

    @TypeConverter
    fun fromMemberRules(value: ApiCalendar.MemberRules?): String? {
        return value?.let { Json.encodeToString(it) }
    }

    @TypeConverter
    fun toMemberRules(value: String?): ApiCalendar.MemberRules? {
        return value?.let { Json.decodeFromString(it) }
    }
}