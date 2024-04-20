package cz.cvut.fit.localstorage.notes

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch
import java.util.UUID

class NotesViewModel : ViewModel() {

    private val _screenStateStream = MutableStateFlow(NotesScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        NotesDataSource.getAllStream()
            .onEach { notes -> _screenStateStream.update { it.copy(notes = notes) } }
            .launchIn(viewModelScope)
    }

    fun onAddClick() {
        viewModelScope.launch {
            NotesDataSource.insert(Note(text = UUID.randomUUID().toString()))
        }
    }

    fun onDeleteClick(note: Note) {
        viewModelScope.launch {
            NotesDataSource.delete(note)
        }
    }

    fun onRefreshClick(note: Note) {
        viewModelScope.launch {
            val newNote = note.copy(text = UUID.randomUUID().toString())
            NotesDataSource.update(newNote)
        }
    }

    fun onDeleteAllClick() {
        viewModelScope.launch {
            NotesDataSource.deleteAll()
        }
    }
}

data class NotesScreenState(
    val notes: List<Note> = emptyList(),
)
