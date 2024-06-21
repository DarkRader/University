package cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ArrowBack
import androidx.compose.material.icons.filled.Add
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.Edit
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import cz.cvut.fit.kuznear1.bukreservationapp.R

// Custom Top Bars that repeats in different features

@Composable
fun ListTopBar(
    headerText: String,
    onNavigateBackClick: () -> Unit,
    onAddClick: () -> Unit,
) {
    Column {
        TopAppBar(
            navigationIcon = {
                IconButton(onClick = onNavigateBackClick) {
                    Icon(
                        Icons.AutoMirrored.Filled.ArrowBack,
                        contentDescription = stringResource(id = R.string.back_button),
                        tint = MaterialTheme.colorScheme.onPrimary,
                    )
                }
            },
            title = {
                Text(
                    text = headerText,
                    style = MaterialTheme.typography.headlineMedium,
                    color = MaterialTheme.colorScheme.onPrimary
                )
            },
            actions = {
                IconButton(onClick = onAddClick) {
                    Icon(
                        Icons.Default.Add,
                        contentDescription = stringResource(id = R.string.add_button),
                    )
                }
            },
            colors = TopAppBarDefaults.topAppBarColors(
                containerColor = MaterialTheme.colorScheme.secondaryContainer
            )
        )
        HorizontalDivider(
            modifier = Modifier.fillMaxWidth(),
            thickness = 1.dp,
            color = MaterialTheme.colorScheme.onPrimary
        )
    }
}

@Composable
fun DetailTopBar(
    headerText: String,
    onEditClick: () -> Unit,
    onDeleteClick: () -> Unit,
    onNavigateBackClick: () -> Unit,
) {
    Column {
        TopAppBar(
            navigationIcon = {
                IconButton(onClick = onNavigateBackClick) {
                    Icon(
                        Icons.AutoMirrored.Filled.ArrowBack,
                        contentDescription = stringResource(id = R.string.back_button),
                        tint = MaterialTheme.colorScheme.onPrimary,
                    )
                }
            },
            title = {
                Text(
                    text = headerText,
                    style = MaterialTheme.typography.headlineMedium,
                    color = MaterialTheme.colorScheme.onPrimary
                )
            },
            actions = {
                IconButton(onClick = onEditClick) {
                    Icon(
                        Icons.Default.Edit,
                        contentDescription = stringResource(id = R.string.edit_button),
                    )
                }
                DeleteButtonWithConfirmationDialog(
                    onDeleteClick = onDeleteClick,
                    onNavigateBackClick = onNavigateBackClick,
                )
            },
            colors = TopAppBarDefaults.topAppBarColors(
                containerColor = MaterialTheme.colorScheme.secondaryContainer
            )
        )
        HorizontalDivider(
            modifier = Modifier.fillMaxWidth(),
            thickness = 1.dp,
            color = MaterialTheme.colorScheme.onPrimary
        )
    }
}

@Composable
fun DeleteButtonWithConfirmationDialog(
    onDeleteClick: () -> Unit,
    onNavigateBackClick: () -> Unit,
) {
    var showDialog by remember { mutableStateOf(false) }

    if (showDialog) {
        AlertDialog(
            onDismissRequest = { showDialog = false },
            title = { Text(text = "Confirmation") },
            text = { Text(text = "Are you sure you want to delete?") },
            confirmButton = {
                Button(
                    onClick = {
                        onNavigateBackClick()
                        onDeleteClick()
                        showDialog = false
                    }
                ) {
                    Text(text = "Yes")
                }
            },
            dismissButton = {
                Button(
                    onClick = { showDialog = false }
                ) {
                    Text(text = "No")
                }
            }
        )
    }

    IconButton(
        onClick = { showDialog = true }
    ) {
        Icon(
            Icons.Default.Delete,
            contentDescription = stringResource(id = R.string.delete_button),
        )
    }
}

@Composable
fun AddTopBar(
    headerText: String,
    onNavigateBackClick: () -> Unit,
) {
    Column {
        TopAppBar(
            navigationIcon = {
                IconButton(onClick = onNavigateBackClick) {
                    Icon(
                        Icons.AutoMirrored.Filled.ArrowBack,
                        contentDescription = stringResource(id = R.string.back_button),
                        tint = MaterialTheme.colorScheme.onPrimary,
                    )
                }
            },
            title = {
                Text(
                    text = headerText,
                    style = MaterialTheme.typography.headlineMedium,
                    color = MaterialTheme.colorScheme.onPrimary
                )
            },
            colors = TopAppBarDefaults.topAppBarColors(
                containerColor = MaterialTheme.colorScheme.secondaryContainer
            )
        )
        HorizontalDivider(
            modifier = Modifier.fillMaxWidth(),
            thickness = 1.dp,
            color = MaterialTheme.colorScheme.onPrimary
        )
    }
}