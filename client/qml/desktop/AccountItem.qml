import QtQuick 1.0
import QtDesktop 0.1

Column {
	id: column
	property string label
	property string value
	spacing: 5

	Text {
		id: labelField
		text: column.label + ":"
	}

	TextField {
		id: valueField
		readOnly: true
		text: column.value
	}
}
