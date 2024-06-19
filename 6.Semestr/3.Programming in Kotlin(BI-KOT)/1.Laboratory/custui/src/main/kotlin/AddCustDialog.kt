package fit.bikot.custui

import fit.bikot.ratio.custFacade
import javafx.scene.Parent
import javafx.scene.control.TextField
import tornadofx.*

class AddCustDialog : Fragment() {
    lateinit var tf: TextField
    override val root =
        form {
            fieldset {
                field("Name:") {
                    tf = textfield()
                }
            }
            buttonbar {
                button("ok") {
                    action {
                        custFacade.create(tf.text)
                        find<CustView>().custData.setAll(custFacade.all)
                        println(find<CustView>().custData)
                        close()
                    }
                }
                button("Cancel") {
                    action {
                        close()
                    }
                }
            }

        }
}