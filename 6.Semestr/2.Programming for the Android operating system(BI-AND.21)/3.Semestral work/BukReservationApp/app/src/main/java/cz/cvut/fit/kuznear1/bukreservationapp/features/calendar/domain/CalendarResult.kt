package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain

data class CalendarsResult(
    val calendars: List<Calendar>,
    val isSuccess: Boolean,
)

data class CalendarResult(
    val calendar: Calendar?,
    val isSuccess: Boolean,
)