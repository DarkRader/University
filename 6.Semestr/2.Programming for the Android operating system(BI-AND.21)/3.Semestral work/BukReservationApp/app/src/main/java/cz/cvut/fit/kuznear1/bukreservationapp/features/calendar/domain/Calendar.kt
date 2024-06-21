package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain

import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api.ApiCalendar
import kotlinx.serialization.Serializable

@Serializable
data class Calendar(
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

fun CreateDefaultCalendar(): Calendar {
    val rules = ApiCalendar.MemberRules(
        night_time = false,
        reservation_more_24_hours = false,
        in_advance_hours = 0,
        in_advance_minutes = 0,
        in_advance_day = 0,
    )

    return Calendar(
        calendar_id = "",
        service_alias = "",
        reservation_type = "",
        event_name = "",
        max_people = 0,
        collision_with_itself = false,
        collision_with_calendar = emptyList(),
        club_member_rules = rules,
        active_member_rules = rules,
        manager_rules = rules,
        mini_services = null
    )
}