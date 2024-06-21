package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain

import androidx.compose.ui.graphics.Color
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.theme.*

data class ReservationChip(
    val reservationService: String,
    val serviceAlias: String,
    val chooseColor: Color,
    val backgroundColor: Color,
)

object ReservationChipDataSource {

    private val reservationChips = listOf(
        ReservationChip(
            reservationService = "Club Room reservation",
            serviceAlias = "klub",
            chooseColor = ClubRoomChooseColor,
            backgroundColor = ClubRoomBackgroundColor,
        ),
        ReservationChip(
            reservationService = "Grill reservation",
            serviceAlias = "grill",
            chooseColor = GrillChooseColor,
            backgroundColor = GrillBackgroundColor,
        ),
        ReservationChip(
            reservationService = "Study Room reservation",
            serviceAlias = "stud",
            chooseColor = StudyRoomChooseColor,
            backgroundColor = StudyRoomBackgroundColor,
        ),
    )

    fun getAll(): List<ReservationChip> = reservationChips
}
