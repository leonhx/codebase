package suggestions
package gui

import javax.swing.UIManager

import rx.lang.scala.{Observable, Subscription}
import scala.concurrent.ExecutionContext.Implicits.global
import suggestions.observablex._
import suggestions.search._

import scala.collection.mutable.ListBuffer
import scala.swing.Orientation._
import scala.swing.Swing._
import scala.swing._
import scala.swing.event._
import scala.util.{Failure, Success, Try}

object WikipediaSuggest extends SimpleSwingApplication with ConcreteSwingApi with ConcreteWikipediaApi {

  {
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName())
    } catch {
      case t: Throwable =>
    }
  }

  def top = new MainFrame {

    /* gui setup */

    title = "Query Wikipedia"
    minimumSize = new Dimension(900, 600)

    val button = new Button("Get") {
      icon = new javax.swing.ImageIcon(javax.imageio.ImageIO.read(this.getClass.getResourceAsStream("/suggestions/wiki-icon.png")))
    }
    val searchTermField = new TextField
    val suggestionList = new ListView(ListBuffer[String]())
    val status = new Label(" ")
    val editorpane = new EditorPane {
      import javax.swing.border._
      border = new EtchedBorder(EtchedBorder.LOWERED)
      editable = false
      peer.setContentType("text/html")
    }

    contents = new BoxPanel(orientation = Vertical) {
      border = EmptyBorder(top = 5, left = 5, bottom = 5, right = 5)
      contents += new BoxPanel(orientation = Horizontal) {
        contents += new BoxPanel(orientation = Vertical) {
          maximumSize = new Dimension(240, 900)
          border = EmptyBorder(top = 10, left = 10, bottom = 10, right = 10)
          contents += new BoxPanel(orientation = Horizontal) {
            maximumSize = new Dimension(640, 30)
            border = EmptyBorder(top = 5, left = 0, bottom = 5, right = 0)
            contents += searchTermField
          }
          contents += new ScrollPane(suggestionList)
          contents += new BorderPanel {
            maximumSize = new Dimension(640, 30)
            add(button, BorderPanel.Position.Center)
          }
        }
        contents += new ScrollPane(editorpane)
      }
      contents += status
    }

    val eventScheduler = SchedulerEx.SwingEventThreadScheduler

    /**
     * Observables
     * You may find the following methods useful when manipulating GUI elements:
     *  `myListView.listData = aList` : sets the content of `myListView` to `aList`
     *  `myTextField.text = "react"` : sets the content of `myTextField` to "react"
     *  `myListView.selection.items` returns a list of selected items from `myListView`
     *  `myEditorPane.text = "act"` : sets the content of `myEditorPane` to "act"
     */

    // TO IMPLEMENT
    val searchTerms: Observable[String] = searchTermField.textValues

    // TO IMPLEMENT
    val suggestions: Observable[Try[List[String]]] = searchTerms.flatMap(wikiSuggestResponseStream(_).recovered)

    // TO IMPLEMENT
    val suggestionSubscription: Subscription =  suggestions.observeOn(eventScheduler) subscribe { x =>
      x match {
        case Success(l) => suggestionList.listData = l
        case Failure(e) => status.text = e.getMessage
      }
    }

    // TO IMPLEMENT
    val selections: Observable[String] = button.clicks.map(_ => suggestionList.selection.items.head)

    // TO IMPLEMENT
    val pages: Observable[Try[String]] = selections.flatMap(term => ObservableEx(wikipediaPage(term)).timedOut(5L).recovered )

    // TO IMPLEMENT
    val pageSubscription: Subscription = pages.observeOn(eventScheduler) subscribe { x =>
      x match {
        case Success(p) => editorpane.text = p
        case Failure(e) => status.text = e.getMessage
      }
    }

  }

}


trait ConcreteWikipediaApi extends WikipediaApi {
  def wikipediaSuggestion(term: String) = Search.wikipediaSuggestion(term)
  def wikipediaPage(term: String) = Search.wikipediaPage(term)
}


trait ConcreteSwingApi extends SwingApi {
  type ValueChanged = scala.swing.event.ValueChanged
  object ValueChanged {
    def unapply(x: Event) = x match {
      case vc: ValueChanged => Some(vc.source.asInstanceOf[TextField])
      case _ => None
    }
  }
  type ButtonClicked = scala.swing.event.ButtonClicked
  object ButtonClicked {
    def unapply(x: Event) = x match {
      case bc: ButtonClicked => Some(bc.source.asInstanceOf[Button])
      case _ => None
    }
  }
  type TextField = scala.swing.TextField
  type Button = scala.swing.Button
}
