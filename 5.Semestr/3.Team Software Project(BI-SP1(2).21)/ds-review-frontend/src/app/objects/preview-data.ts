/**
 * @param img_src: path to image
 * @param text_1: text nr. 1 in the card preview
 * @param text_2: text nr. 2 in the card preview
 * @param new_events_count: number of new events
 * which occured since user clicked the card last time
 * @param show_icon: if @param new_events_count should be displayed ... T/F
 * @param background_color: background color of the card
 * @param text_color: color of text
 */
export interface PreviewData {
  img_src: String
  text_1: String
  text_2: String
  new_events_count: Number
  show_icon: boolean
  background_color: String
  text_color: String
  uuid: String
}
