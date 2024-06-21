package cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.Checkbox
import androidx.compose.material3.CheckboxDefaults
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TextFieldDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import cz.cvut.fit.kuznear1.bukreservationapp.R
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar

// Custom text styles in different format that repeats in different features

@Composable
fun FieldTextString(
    body: String,
    header: String,
    text: String,
    onTextChanged: (String) -> Unit
)
{

    Column {
        TextSecondHeader(header = header)

        TextField(
            modifier = Modifier
                .fillMaxWidth(),
            value = text,
            onValueChange = { onTextChanged(it) },
            textStyle = MaterialTheme.typography.bodyMedium,
            placeholder = {
                Text(
                    text = body,
                    style = MaterialTheme.typography.bodyLarge,
                    color = MaterialTheme.colorScheme.onSecondary,
                )
            },
            colors = TextFieldDefaults.colors(
                focusedContainerColor = Color.Transparent,
                unfocusedContainerColor = Color.Transparent,
                focusedIndicatorColor = Color.Transparent,
                unfocusedIndicatorColor = Color.Transparent,
                focusedTextColor = MaterialTheme.colorScheme.onPrimary,
            ),
            keyboardOptions = KeyboardOptions.Default.copy(
                imeAction = ImeAction.Done
            )
        )
    }
}

@Composable
fun FieldTextInt(
    body: String,
    header: String,
    number: Int,
    onNumberChanged: (Int) -> Unit
)
{

    val textState = remember { mutableStateOf(number.toString()) }

    Column {
        TextSecondHeader(header = header)

        TextField(
            modifier = Modifier
                .fillMaxWidth(),
            value = textState.value,
            onValueChange = { newValue ->
                textState.value = newValue
                newValue.toIntOrNull()?.let {
                    onNumberChanged(it)
                }
            },
            textStyle = MaterialTheme.typography.bodyMedium,
            placeholder = {
                Text(
                    text = body,
                    style = MaterialTheme.typography.bodyLarge,
                    color = MaterialTheme.colorScheme.onSecondary,
                )
            },
            colors = TextFieldDefaults.colors(
                focusedContainerColor = Color.Transparent,
                unfocusedContainerColor = Color.Transparent,
                focusedIndicatorColor = Color.Transparent,
                unfocusedIndicatorColor = Color.Transparent,
                focusedTextColor = MaterialTheme.colorScheme.onPrimary,
            ),
            keyboardOptions = KeyboardOptions.Default.copy(
                imeAction = ImeAction.Done,
                keyboardType = KeyboardType.Number
            )
        )
    }
}

@Composable
fun CheckBoxList(
    items: List<Calendar>,
    selectedItems: List<String>,
    onItemCheckedChange: (String, Boolean) -> Unit
) {
    items.forEach { item ->
        CustomCheckBox(
            text = item.reservation_type,
            checked = selectedItems.contains(item.calendar_id),
            onCheckedChange = { isChecked -> onItemCheckedChange(item.calendar_id, isChecked) }
        )
    }
}

@Composable
fun CheckBoxListString(
    items: List<String>,
    selectedItems: List<String>,
    onItemCheckedChange: (String, Boolean) -> Unit
) {
    items.forEach { item ->
        CustomCheckBox(
            text = item,
            checked = selectedItems.contains(item),
            onCheckedChange = { isChecked -> onItemCheckedChange(item, isChecked) }
        )
    }
}

@Composable
fun CustomCheckBox(
    text: String,
    checked: Boolean,
    onCheckedChange: (Boolean) -> Unit
)
{
    Column {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .clickable { onCheckedChange(!checked) },
            verticalAlignment = Alignment.CenterVertically
        ) {
            Checkbox(
                checked = checked,
                onCheckedChange = onCheckedChange,
                colors = CheckboxDefaults.colors(
                    checkedColor = MaterialTheme.colorScheme.primary,
                    uncheckedColor = MaterialTheme.colorScheme.onSecondary,
                    checkmarkColor = MaterialTheme.colorScheme.onPrimary
                )
            )
            Text(
                text = text,
                style = MaterialTheme.typography.bodyMedium,
                modifier = Modifier.padding(start = 8.dp)
            )
        }
    }
}

@Composable
fun CustomDropBox(
    body: String,
    header: String,
    chosenOption: String,
    onTextChanged: (String) -> Unit,
    options: List<String>
)
{
    var expanded by remember { mutableStateOf(false) }

    Column {
        TextSecondHeader(header = header)

        Box(
            modifier = Modifier.fillMaxWidth(),
            contentAlignment = Alignment.CenterStart
        ) {
            Row(
                verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier
                    .clickable { expanded = true }
                    .padding(vertical = 12.dp, horizontal = 16.dp)
            ) {
                Text(
                    text = chosenOption.takeIf { it.isNotEmpty() } ?: body,
                    style = MaterialTheme.typography.bodyMedium,
                )
                Icon(
                    painter = painterResource(id = R.drawable.ic_baseline_arrow_drop_down_24),
                    contentDescription = "Dropdown Arrow",
                    modifier = Modifier.size(24.dp)
                )
            }

            DropdownMenu(
                expanded = expanded,
                onDismissRequest = { expanded = false },
            ) {
                options.forEach { label ->
                    DropdownMenuItem(
                        text = {
                            Text(
                                text = label,
                                style = MaterialTheme.typography.bodyLarge,
                                color = MaterialTheme.colorScheme.onSecondary,
                            ) },
                        onClick = {
                            onTextChanged(label)
                            expanded = false
                        }
                    )

                }
            }
        }
    }
}

@Composable
fun TextHeaderStyle(body: Any, header: String) {
    Column {
        TextSecondHeader(header = header)
        TextBodyStyle(body = body)
    }
}

@Composable
private fun TextBodyStyle(body: Any) {
    Text(
        text = when (body) {
            is String -> body
            is Int -> body.toString()
            is Boolean -> if (body) "Enabled" else "Disabled"
            else -> "Unsupported type"
        },
        style = MaterialTheme.typography.bodyMedium,
        color = MaterialTheme.colorScheme.onSecondary,
    )
}

@Composable
fun TextSecondHeader(header: String) {
    Text(
        text = header,
        style = MaterialTheme.typography.headlineSmall,
        color = MaterialTheme.colorScheme.primary,
    )
}

@Preview
@Composable
fun PreviewTextHeaderStyle(

) {
    TextHeaderStyle(
        body = "fwajfwa",
        header = "fwafwafwa"
    ) 

}