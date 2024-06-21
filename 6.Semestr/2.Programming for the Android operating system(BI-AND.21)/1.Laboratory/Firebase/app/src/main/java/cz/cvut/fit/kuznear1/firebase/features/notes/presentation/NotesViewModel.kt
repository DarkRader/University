package cz.cvut.fit.kuznear1.firebase.features.notes.presentation

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.google.firebase.analytics.FirebaseAnalytics
import com.google.firebase.analytics.logEvent
import cz.cvut.fit.kuznear1.firebase.features.notes.data.NotesRepository
import cz.cvut.fit.kuznear1.firebase.features.notes.domain.Note
import cz.cvut.fit.kuznear1.firebase.features.profile.data.UserRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.emptyFlow
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.flow.flatMapLatest
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch
import java.util.UUID

class NotesViewModel(
    private val notesRepository: NotesRepository,
    private val userRepository: UserRepository,
    private val analytics: FirebaseAnalytics,
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(NotesScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    private val userStream = userRepository.userState.stateIn(
        viewModelScope,
        SharingStarted.Eagerly,
        null
    )

    init {
        viewModelScope.launch {
            userStream.flatMapLatest { user ->
                if (user == null) {
                    emptyFlow()
                } else {
                    notesRepository.getNotesStream(user.id)
                }
            }.collect { notes ->
                _screenStateStream.update { it.copy(notes = notes) }
            }
        }
    }

    fun addNote() {
        viewModelScope.launch {
            analytics.logEvent("add_note") {
                param("param_name", "alksdjalksdjlakjsdasl")
            }
            val user = userStream.first() ?: return@launch
            notesRepository.addNote(
                userId = user.id,
                note = Note(
                    text = UUID.randomUUID().toString(),
                    timestamp = System.currentTimeMillis()
                )
            )
        }
    }
}

data class NotesScreenState(
    val notes: List<Note> = listOf(),
)
