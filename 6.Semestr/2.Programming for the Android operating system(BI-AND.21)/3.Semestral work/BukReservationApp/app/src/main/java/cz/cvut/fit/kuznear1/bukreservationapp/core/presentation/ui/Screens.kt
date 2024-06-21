package cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui

sealed class Screens(val route: String) {

    // Calendar feature
    data object CalendarsScreen: Screens("calendars")

    data object CalendarDetailScreen: Screens("calendar_detail") {
        const val ID_KEY = "id"
    }

    data object CalendarAddScreen: Screens("calendar_add")

    data object CalendarEditScreen: Screens("calendar_edit") {
        const val ID_KEY = "id"
    }

    // Mini Services feature
    data object MiniServicesScreen: Screens("mini_services")

    data object MiniServiceDetailScreen: Screens("mini_service_detail") {
        const val ID_KEY = "id"
    }

    data object MiniServiceAddScreen: Screens("mini_service_add")

    data object MiniServiceEditScreen: Screens("mini_service_edit") {
        const val ID_KEY = "id"
    }

    // Profile feature
    data object ProfileScreen: Screens("profile")

    // Reservation feature
    data object MyReservationScreen: Screens("my_reservation")

    data object ReservationScreen: Screens("reservation")

    data object FormScreen: Screens("form") {
        const val ALIAS_KEY = "alias"
    }
}