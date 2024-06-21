package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api

import kotlinx.serialization.Serializable

@Serializable
data class ApiCalendar(
    val calendars: List<Calendar>
) {

    @Serializable
    data class Calendar(
        val calendar_id: String,
        val service_alias: String,
        val reservation_type: String,
        val event_name: String,
        val max_people: Int,
        val collision_with_itself: Boolean,
        val collision_with_calendar: List<String>,
        val club_member_rules: MemberRules,
        val active_member_rules: MemberRules,
        val manager_rules: MemberRules,
        val mini_services: List<String>?
    )

    @Serializable
    data class MemberRules(
        val night_time: Boolean,
        val reservation_more_24_hours: Boolean,
        val in_advance_hours: Int,
        val in_advance_minutes: Int,
        val in_advance_day: Int,
    )

}