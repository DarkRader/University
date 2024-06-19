package fit.bikot.custui

import javafx.scene.Parent
import tornadofx.*

class MyApp: App(MainView::class)

class MainView : View() {
    override val root= borderpane {
        top = menubar {
            menu("Customer") {
                item("Add Customer") {
                    action {
                        find<AddCustDialog>().openModal()
                    }
                }
            }
        }
        center<CustView>()
    }

}

fun main() {
    launch<MyApp>()
}
