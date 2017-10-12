import javax.swing.*;
import javax.swing.table.*;
import javax.swing.border.LineBorder;
import java.io.File;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.Color;

public class MyInterface {
	static public class MyTableModel extends AbstractTableModel {
		public int getColumnCount() {
			return 3;
		}

		public int getRowCount() {
			return 15;
		}

		public Object getValueAt(int rowIndex, int colIndex) {
			Integer value = rowIndex * colIndex;
			return value;
		}
	}

	public static void main(String[] args) {
		//Choose a input file
		
		/*
		JFileChooser fileChooser = new JFileChooser();
		fileChooser.setFileFilter(new FileNameExtensionFilter("Apenas TXT e XML", "txt", "xml"));
		int myRet = fileChooser.showOpenDialog(null);
		if (myRet == JFileChooser.APPROVE_OPTION) {
			//Do shit
			File file = fileChooser.getSelectedFile();
		} else {
			//Failed
		}
		*/

		//Fucked up dialog box
		//JOptionPane.showMessageDialog(null, "Hell on world!\n");

		//Botões
		JButton botaoInput = new JButton("New input");
		botaoInput.setMnemonic(KeyEvent.VK_N);
		JButton botaoSair = new JButton("Exit");
		botaoSair.setMnemonic(KeyEvent.VK_E);

		//Agrupa os botões de forma padrão
		JPanel painel = new JPanel ();
		painel.add(botaoInput); 
		painel.add(botaoSair);

		//Exibe o
		//Main window title
		JFrame window = new JFrame("100% Gambiarra");
		//Set previously made panel to the frame
		window.add(painel);
		//Set default action on pressing the close button
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//Set visible (why the fuck this is not default?)
		window.setVisible(true);
		
		//"It's a good practice spliting the main interface construction
		//in a large nuber of small methods, each one doing a small part of
		//the process. 

		//Implementando uma tabela simples
		JTable myTable = new JTable ();
		myTable.setBorder(new LineBorder(Color.black));
		myTable.setGridColor(Color.black);
		myTable.setShowGrid(true);

		//Implementando uma barra de rolagem para tabelas muito grandes
		JScrollPane scroll = new JScrollPane(); 
		scroll.getViewport().setBorder(null);
		scroll.getViewport().add(myTable); 
		scroll.setSize(450, 450);
		
		painel.add(scroll);

		//Adjust the window
		window.pack();
		window.setSize(540, 540);

		//Delegating buttons their respective actions, with a anonymous class
		botaoSair.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});

		botaoInput.addActionListener(new ActionListener () {
			public void actionPerformed(ActionEvent e) {
				MyTableModel mm = new MyTableModel(); 
				myTable.setModel(mm);
			}
		});

	}
}