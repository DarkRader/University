package cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui

import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.navigation.NavHostController
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.navArgument
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.add.CalendarAddScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.list.CalendarsScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.reservation.ReservationScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.presentation.main_page.ProfileScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.form.FormScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.detail.CalendarDetailScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.edit.CalendarEditScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.list.MiniServicesScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.detail.MiniServiceDetailScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.edit.MiniServiceEditScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.add.MiniServiceAddScreen
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.my_reservation.MyReservationScreen

@Composable
fun Navigation(
    navController: NavHostController,
    modifier: Modifier = Modifier
) {
    NavHost(
        navController = navController,
        startDestination = Screens.ReservationScreen.route,
        modifier = modifier,
    ) {
        // Calendar feature
        composable(route = Screens.CalendarsScreen.route) {
            CalendarsScreen(navController = navController)
        }

        composable(
            route = Screens.CalendarDetailScreen.route + "/{${Screens.CalendarDetailScreen.ID_KEY}}",
            arguments =  listOf(
                navArgument(name = Screens.CalendarDetailScreen.ID_KEY) {
                    type = NavType.StringType
                },
            ),
        ) {
            CalendarDetailScreen(navController = navController)
        }

        composable(route = Screens.CalendarAddScreen.route) {
            CalendarAddScreen(navController = navController)
        }

        composable(
            route = Screens.CalendarEditScreen.route + "/{${Screens.CalendarEditScreen.ID_KEY}}",
            arguments =  listOf(
                navArgument(name = Screens.CalendarEditScreen.ID_KEY) {
                    type = NavType.StringType
                },
            ),
        ) {
            CalendarEditScreen(navController = navController)
        }

        // Mini Services feature
        composable(route = Screens.MiniServicesScreen.route) {
            MiniServicesScreen(navController = navController)
        }

        composable(
            route = Screens.MiniServiceDetailScreen.route + "/{${Screens.MiniServiceDetailScreen.ID_KEY}}",
            arguments =  listOf(
                navArgument(name = Screens.MiniServiceDetailScreen.ID_KEY) {
                    type = NavType.StringType
                },
            ),
        ) {
            MiniServiceDetailScreen(navController = navController)
        }

        composable(route = Screens.MiniServiceAddScreen.route) {
            MiniServiceAddScreen(navController = navController)
        }

        composable(
            route = Screens.MiniServiceEditScreen.route + "/{${Screens.MiniServiceEditScreen.ID_KEY}}",
            arguments =  listOf(
                navArgument(name = Screens.MiniServiceEditScreen.ID_KEY) {
                    type = NavType.StringType
                },
            ),
        ) {
            MiniServiceEditScreen(navController = navController)
        }

        // Profile feature
        composable(route = Screens.ProfileScreen.route) {
            ProfileScreen(navController = navController)
        }


        // Reservation feature
        composable(route = Screens.MyReservationScreen.route) {
            MyReservationScreen(navController = navController)
        }

        composable(route = Screens.ReservationScreen.route) {
            ReservationScreen(navController = navController)
        }

        composable(
            route = Screens.FormScreen.route + "/{${Screens.FormScreen.ALIAS_KEY}}",
            arguments = listOf(
                navArgument(name = Screens.FormScreen.ALIAS_KEY) {
                    type = NavType.StringType
                },
            ),
        ) {
            FormScreen(navController = navController)
        }
    }
}