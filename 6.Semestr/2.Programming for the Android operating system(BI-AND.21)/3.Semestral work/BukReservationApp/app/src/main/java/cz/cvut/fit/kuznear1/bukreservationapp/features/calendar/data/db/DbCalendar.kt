package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.db

import androidx.room.Entity
import androidx.room.PrimaryKey
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api.ApiCalendar

@Entity(tableName = "calendar")
data class DbCalendar(
    @PrimaryKey
    val calendar_id: String,
    val service_alias: String,
    val reservation_type: String,
    val event_name: String,
    val max_people: Int,
    val collision_with_itself: Boolean,
    val collision_with_calendar: List<String>,
    val club_member_rules: ApiCalendar.MemberRules,
    val active_member_rules: ApiCalendar.MemberRules,
    val manager_rules: ApiCalendar.MemberRules,
    val mini_services: List<String>?
)
