/*!
    \file principalGrafo.cpp
    \brief Programa principal de la práctica 4 de ED: Grafo Abarcador de coste mínimo
    \author Carlos Luque Córdoba
    \date   anywhere
    \version 1.0
*/

/*!
 \mainpage Implementación de un Grafo Abarcador de coste mínimo
 \author   Carlos Luque Córdoba
 \date     anywhere
 \version  1.0
*/

// Para los flujos de entrada y salida y para usar locale
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "macros.hpp"
#include "distancia.hpp"
#include "Punto.hpp"
#include "Vertice.hpp"
#include "Lado.hpp"
#include "Grafo.hpp"
#include "funcionesAuxiliares.hpp"

/*! 
    \brief   Programa principal de la práctica 4: Grafo Abarcador de coste mínimo
    \return  int
*/
int main(){
    char nombreFichero2[10];
    std::ifstream grap;
    std::ofstream png;
    bool value;
    std::vector<std::vector<float> > matriz;
    std::vector<ed::Lado<ed::Punto<float> > > l;
    int opcion;
    std::string nombreFichero;
    int directed;
    bool direct, val=false, p=false, k=false;


    std::cout<<RESET<<CLEAR_SCREEN<<std::endl;
    PLACE(1,1);
    std::cout <<BIGREEN<<"BIENVENIDO AL PROGRAMA PRINCIPAL DEL GRAFO DE CARLOS LUQUE CÓRDOBA";
    PLACE(2,3);

    std::cout <<BIBLUE<<"\nEl grafo es dirigido (1) o no dirigido (2): ";
    std::cin>>directed;
    std::cout<<RESET<<CLEAR_SCREEN<<std::endl;
    if(directed==1 || directed==2){
        switch(directed){
            case 1:
                direct=true;
                break;
            
            case 2:
                direct=false;
                break;
        }
    }else{
        std::cout<<BIRED<<"OPCIÓN "<<directed<<" NO VALIDA!!"<<RESET<<std::endl;
        exit(-1);
    }

    ed::Grafo <ed::Punto<float> > graph(direct);
    ed::Grafo <ed::Punto<float> > graph2(direct);
    ed::Grafo <ed::Punto<float> > graph3(direct);
    do{
        // Se elige la opción del menún
        opcion = ed::menu();        

        std::cout << CLEAR_SCREEN;
        PLACE(3,1);

        // Se ejecuta la opción del menú elegida
        switch(opcion){
            case 0: 
                    std::cout << INVERSE;
                    std::cout << "Fin del programa" << std::endl;
                    std::cout << RESET;
            break;

           ///////////////////////////////////////////////////////////////////

            case 1: 
                std::cout<<BIPURPLE<< "[1] Comprobar si el Grafo tiene vertices"<<RESET<< std::endl;
                if(graph.getVectorVertices().size()==0)
                    std::cout<<ONIRED<<BIYELLOW<<"El Grafo está vacío"<<RESET<<std::endl;
                else
                    std::cout<<BIGREEN<<"Al menos hay un Verice en el Grafo"<<RESET<<std::endl;
                break;

            //////////////////////////////////////////////////////////////////////////////
            case 2: 
                std::cout<<BIPURPLE<<"[2] Cargar el Grafo de vertices y/o lados desde ficheros"<<RESET<<std::endl;
                ed::cargarFichero(graph);
                break;

            case 3:
                PLACE(1,1);
                std::cout<<BIPURPLE<<"[3] Grabar las matrices de adyacencia en un fichero"<<RESET<<std::endl;
                if(graph.getVectorVertices().size()>0){
                    val=ed::grabarFichero(graph);
                    k=val;
                    p=val;
                }else{
                    std::cout<<ONIRED<<BIYELLOW<<"El Grafo está vacío"<<RESET<<std::endl;
                }
                break;

            //////////////////////////////////////////////////////////////////////////////
            case 4: 
                std::cout <<BIPURPLE<< "[4] Mostrar los vertices y lados del Grafo" <<RESET<< std::endl;
                if(graph.getVectorVertices().size()<2 && graph.getVectorLado().size()<1){
                    std::cout<<ONIRED<<BIYELLOW<<"No hay vertices o lados para mostrar"<<RESET<<std::endl;
                }else{
                    if(graph.getVectorVertices().size()>0){
                        PLACE(1,1);
                        std::cout <<BIYELLOW<< "Estos son los vertices del Grafo" <<RESET<< std::endl;
                        graph.imprimirVertices();
                        PLACE(25,1);
                        std::cout << "Pulse ";
                        std::cout << BIGREEN;
                        std::cout << "ENTER";
                        std::cout << RESET;
                        std::cout << " para mostrar la siguiente ";
                        std::cout << INVERSE;
                        std::cout << "los lados"; 
                        std::cout << RESET;

                        // Pausa
                        std::cin.ignore();
                        PLACE(2,1);
                        std::cout << CLEAR_SCREEN;
                    }
                    if(graph.getVectorLado().size()>0){
                        std::cout <<BIYELLOW<< "Estos son los lados del Grafo" <<RESET<< std::endl;
                        graph.imprimirLados();
                        PLACE(25,1);
                        std::cout << "Pulse ";
                        std::cout << BIGREEN;
                        std::cout << "ENTER";
                        std::cout << RESET;
                        std::cout << " para mostrar la siguiente ";
                        std::cout << INVERSE;
                        std::cout << "el menú"; 
                        std::cout << RESET;
                        PLACE(2,1);
                    }
                }
                break;

            case 5: 
                    std::cout<<BIPURPLE<< "[5] Mostrar la Matriz de Adyacencias: " <<RESET<< std::endl;
                    if(graph.getVectorVertices().size()<2 && graph.getVectorLado().size()<1){
                        std::cout<<ONIRED<<BIYELLOW<<"No hay suficientes vertices y lados como para crear una matriz"<<RESET<<std::endl;
                    }else{
                        graph.crearMatriz(graph.getVectorVertices(), graph.getVectorLado(), graph.getVectorEtiquetas().size()+1);
                        graph.crearMatrizSinLabels(graph.getVectorVertices(), graph.getVectorLado());
                        graph.imprimirMatriz(graph.getVectorVertices(), graph.getMatriz(), graph.getVectorEtiquetas().size()+1);
                        val=true;
                    }
                    break;


            //////////////////////////////////////////////////////////////////////////////
            case 6: 
                std::cout <<BIPURPLE<<"[6] Algoritmo de Prim"<<RESET<< std::endl;
                if(val==false){
                    std::cout<<ONIRED<<BIYELLOW<<"Matriz de Adyacencias no creada aún"<<RESET<<std::endl;
                }else{
                    graph2.setMatrizWLabels(ed::prim(graph, graph2));
                    graph.imprimirMatrizSinLabels(graph.getVectorVertices(), graph2.getMatrizWLabels());
                    graph.recogerCamino(graph.getPadre(), graph.getHijo(), graph.getCoste());
                    std::cout<<BIWHITE<<"El coste mínimo del arbol abarcador de Prim es: "<<graph.getMax()<<RESET<<std::endl;
                    p=true;
                }
                break;

            case 7: 
                std::cout <<BIPURPLE<< "[7] Algoritmo de Kruskal"<<RESET<< std::endl;
                if(val==false){
                    std::cout<<ONIRED<<BIYELLOW<<"Matriz de Adyacencias no creada aún"<<RESET<<std::endl;
                }else{
                    graph2.setMatrizWLabels(ed::kruskal(graph, graph2));
                    graph.imprimirMatrizSinLabels(graph.getVectorVertices(), graph2.getMatrizWLabels());
                    graph.recogerCamino(graph.getPadre(), graph.getHijo(), graph.getCoste());
                    std::cout<<BIWHITE<<"El coste mínimo del arbol abarcador de Kruskal es: "<<graph.getMax()<<RESET<<std::endl;
                    k=true;
                }
                break;

            case 8: 
                    std::cout <<BIPURPLE<< "[8] Borrar un Vertice" <<RESET<<std::endl;
                    //graph.removeVertex();
                    break;

            //////////////////////////////////////////////////////////////////////////////
            case 9: 
                    std::cout <<BIPURPLE<< "[9] Borrar todos los vertices y lados" <<RESET<< std::endl;
                    if(graph.getVectorVertices().size()==0)
                        std::cout<<ONIRED<<BIYELLOW<<"El Grafo ya está vacío"<<RESET<<std::endl;
                    else{
                        std::cout<<BIYELLOW<<"Se va a proceder a eliminar los "<<graph.getVectorVertices().size()<<" vertices y "<<graph.getVectorLado().size()<<" lados del grafo"<<RESET<<std::endl;
                        graph.removeAllVertexAndEdges();   
                        std::cout<<BIWHITE<<"Actualmente hay "<<graph.getVectorVertices().size()<<" vertices y "<<graph.getVectorLado().size()<<" lados en el grafo"<<RESET<<std::endl;
                        if(graph.getVectorVertices().size()==0 && graph.getVectorLado().size()==0)
                            std::cout<<BIGREEN<<"Se han eliminado los elementos del grafo correctamente"<<RESET<<std::endl;
                    }               
                    break;

            case 10: 
                    std::cout <<BIPURPLE<< "[10] Insertar una Vertice" <<RESET<< std::endl;
                    break;

            case 11: 
                    std::cout <<BIPURPLE<< "[11] Insertar un Lado" <<RESET<<std::endl;
                    break;
            case 12: 
                    std::cout <<BIPURPLE<< "[12] Generar el Grafo en PNG" <<RESET<<std::endl;
                    std::cout<<BIRED<<"SI ES NO DIRIGIDO NO SE DEBE REPRESENTAR EL PNG O SOLO COGER LOS LADOS 1 VEZ NO DE IDA Y VUELTA"<<RESET<<std::endl;
                    if(graph.getVectorVertices().size()==0)
                        std::cout<<ONIRED<<BIYELLOW<<"El Grafo está vacío y no se puede generar el PNG del Grafo"<<RESET<<std::endl;
                    else{
                        std::cout<<BIBLUE<<"Introduce el nombre del fichero acabado en .dot: ";
                        nombreFichero="grafoDirigido.dot";
                        std::cout<<RESET<<std::endl;
                        l=graph.getVectorLado();
                        png.open(nombreFichero.c_str());
                        if(png.is_open()){
                            png<<l;               
                            png.close();
                            value=true;
                        }else
                            value=false;
                        
                        if(value){
                            std::cout<<BIGREEN<<"\nEl fichero .dot ha sido generado con exito, debe ejecutar el comando que se \nadjunta en el fichero comando.txt situado en el directorio"<<RESET<<std::endl;
                        }
                        else{
                            std::cout<<BIRED<<"Error al cargar el fichero"<<RESET<<std::endl;
                            std::cin.ignore();
                        }
                    }
                    break;

            case 13:
                std::cout <<BIBLUE<< "[13] Generar el PNG de Prim y Kruskal"<<RESET<<std::endl;
                if(p && k){
                    ed::generarPNGPrim(nombreFichero2, graph.getPadre(), graph.getHijo(), graph.getCoste());
                    ed::generarPNGKruskal(nombreFichero2, graph.getPadre(), graph.getHijo(), graph.getCoste());
                    std::cout<<BIYELLOW<<"Deberá ejecutar los comandos almacenados en el fichero comandos del directorio"<<RESET<<std::endl;
                    std::cin.ignore();
                }else{
                    std::cout<<ONIRED<<BIYELLOW<<"Aún no se ha usado el Algoritmo de Prim o el de Kruskal"<<RESET<<std::endl;
                }
                break;
            //////////////////////////////////////////////////////////////////////////////
            default:
                std::cout << BIRED;
                std::cout << "Opción incorrecta ";
                std::cout << RESET;
                std::cout << "--> ";
                std::cout << ONIRED;
                std::cout << opcion << std::endl;
                std::cout << RESET;
     }
  
    if (opcion !=0)
    {
        PLACE(25,1);
        std::cout << "Pulse ";
        std::cout << BIGREEN;
        std::cout << "ENTER";
        std::cout << RESET;
        std::cout << " para mostrar el ";
        std::cout << INVERSE;
        std::cout << "menú"; 
        std::cout << RESET;

        // Pausa
        std::cin.ignore();

        std::cout << CLEAR_SCREEN;
    }
      }while(opcion!=0);

    return 0;
}
