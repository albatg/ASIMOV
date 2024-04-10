/**
 *@file asimov_library.h
 *@version 1.0
 *@date 22/02/2024
 *@author Grupo ASIMOV
 *@title Librería para proyecto interdisciplinar de modelización del proceso de la glucólisis en una célula
*
*/

#ifndef ASIMOV_LIBRARY_H
#define ASIMOV_LIBRARY_H
#include <QTextEdit>
#include<QString>


#endif // ASIMOV_LIBRARY_H

class TPathway;


/**
 *@brief Definición de la clase TRawInput que implementa un tipo de dato para poder gestionar los archivos de entrada
 *       del programa.
*/
class TRawInput : public QObject
{
    private:    // private members
        /**
         * @brief Variable booleana que indica si se ha cargado un archivo
        */
        bool m_loaded;
        /**
         * @brief Variable de tipo QString en el que se guardará el contenido del archivo
        */
        QString* m_source;

    public:
        /**
         * @brief Constructor por defecto de la clase
         * @param v_source Apunta a nullptr por defecto.
         * @post Genera una instancia de la clase TRawInput con su contenido vacío.
        */
        TRawInput(QString* v_source = nullptr);

        /**
         * @brief Destructor de instancias de tipo TRawInput
         *
        */
        ~TRawInput();

        //getters/setters
        /**
         * @brief Método que devuelve el contenido de una fuente
         * @return Devuelve un QString que se corresponde con el valor de la fuente.
        */
        QString getSource();

        /**
         * @brief Método que establece el valor de la fuente.
         * @param v_source Puntero a un objeto QString que se asignará como fuente.
         * @post El objeto m_source queda apuntando al objeto QString proporcionado.
        */
        void setSource(QString& v_source);

        /**
         * @brief Método que devuelve si se ha cargado una fuente(archivo) o no.
         * @return Devuelve true en función de si m_source tiene contenido, en caso contrario devuelve false.
        */
        bool getLoaded();

        //public methods
        /**
         * @brief Intenta cargar contenido desde un archivo a m_source.
         * @details Este método verifica que m_source esté configurada y no esté vacía.
         *          Luego intenta abrir el archivo indicado por m_source en modo de solo lectura.
         *          Si la apertura del archivo es exitosa, lee su contenido y lo almacena en m_source.
         *          Finalmente, marca m_loaded como verdadero y muestra un mensaje de éxito en la consola.
         * @return Devuelve true si la carga desde el archivo fue exitosa, false en caso contrario.
        */
        bool loadFromFile();

        void setToFile();
        void Edit(QTextEdit* editor);

        /**
         * @brief Crea un nuevo documento y lo prepara para su uso.
         * @details Este método se utiliza para crear un nuevo documento. Prepara la instancia m_source
         *          para recibir un objeto QString nuevo.
         */
        void newRawInput();
        unsigned short verifyModel();
        bool createModel(TPathway& v_model);

        /**
         * @brief Limpia el contenido del documento actual.
         * @details Este método se utiliza para limpiar el contenido del documento actual
         *          (si existe) y restablecer la variable m_loaded a falso, indicando que
         *          el documento no está cargado.
         */
        void clean();
};
//=========================================================


// --------------------------------------------------------
//                     TModelMetabolite
// --------------------------------------------------------

/**
 * @brief Clase que encapsula información sobre un metabolito y se utiliza para representar y manipular metabolitos específicos.
 */

class TModelMetabolite
{
private:
    /**
     @brief Nombre del metabolito
    */
    QString m_name;

    /**
     @brief Identificador único del metabolito
    */
    QString m_id;

    /**
     @brief Valor inicial del metabolito
    */
    double m_initValue;

    /**
     @brief Valor máximo permitido para el metabolito
    */
    double m_topValue;

    /**
     @brief Valor mínimo permitido para el metabolito
    */
    double m_bottomValue;

    /**
     @brief  Valor actual del metabolito
    */
    double m_value;

    /**
     @brief Precisión asociada al valor del metabolito
    */
    double m_precision;

    /**
     @brief Etiqueta para marcar el metabolito según necesidades específicas
    */
    bool m_tag;

public:
    // constructor

    /**
     * @brief Constructor de la clase TModelMetabolite.
     * @param m_name Nombre del metabolito.
     * @param m_id Identificador único del metabolito.
     * @param m_initValue Valor inicial del metabolito.
     * @param m_topValue Valor máximo permitido para el metabolito.
     * @param m_bottomValue Valor mínimo permitido para el metabolito.
     * @param m_value Valor actual del metabolito.
     * @param m_precision Precisión asociada al valor del metabolito.
     * @param m_tag Etiqueta para marcar el metabolito según necesidades específicas.
     */
    TModelMetabolite(QString m_name, QString m_id, double m_initValue, double m_topValue,
                     double m_bottomValue, double m_value, double m_precision, bool m_tag);


    // getters/setters

    /**
     * @brief Obtiene el nombre del metabolito.
     * @return Nombre del metabolito.
     */
    QString getName();

    /**
     * @brief Obtiene el identificador único del metabolito.
     * @return Identificador único del metabolito.
     */
    QString getId();

    /**
     * @brief Obtiene el valor inicial del metabolito.
     * @return Valor inicial del metabolito.
     */
    double getInitValue();

    /**
     * @brief Obtiene el valor máximo permitido para el metabolito.
     * @return Valor máximo permitido para el metabolito.
     */
    double getTopValue();

    /**
     * @brief Obtiene el valor mínimo permitido para el metabolito.
     * @return Valor mínimo permitido para el metabolito.
     */
    double getBottomValue();

    /**
     * @brief Obtiene el valor actual del metabolito.
     * @return Valor actual del metabolito.
     */
    double getValue();

    /**
     * @brief Obtiene la precisión asociada al valor del metabolito.
     * @return Precisión asociada al valor del metabolito.
     */
    double getPrecision();

    /**
     * @brief Obtiene la etiqueta que marca el metabolito según necesidades específicas.
     * @return Etiqueta del metabolito.
     */
    bool getTag();

    /**
     * @brief Establece el valor actual del metabolito.
     * @param v_value Nuevo valor para el metabolito.
     */
    void setValue(double v_value);

    /**
     * @brief Establece la etiqueta del metabolito.
     * @param v_tag Nueva etiqueta para el metabolito.
     */
    void setTag(bool v_tag);

    // other methods
    /**
     * @brief Método que calcula el rango (diferencia entre el valor máximo y mínimo permitido) del metabolito.
     * @return Rango del metabolito.
     */
    double range();

};


// --------------------------------------------------------
//                     TModelParameter
// --------------------------------------------------------

/**
 *@brief Esta clase encapsula información sobre un parámetro y se usa para representar y manipular parámetros específicos
 *      relacionados con la glucólisis.
*/

class TModelParameter
{
    private:    // private members
        /**
         *@brief Contador estático utilizado internamente para el índice.
        */
        static short int s_counter;
        /**
         *@brief Índice del parámetro.
        */
        short int m_index;
        /**
         *@brief Identificación única para el parámetro.
        */
        QString m_id;
        /**
         *@brief Decripción del parámetro.
        */
        QString m_description;
        /**
         *@brief Valor numértico del parámetro.
        */
        double m_value;
        /**
         *@brief Precición asociada al valor del parámetro.
        */
        double m_precision;
        /**
         *@brief Etiqueta para marcar en caso de que queramos hacer un uso específico de ese parámetro.
        */
        bool m_tag;

    public:
        // constructor por defecto
       /* TModelParameter(/*short int v_Index = -1 QString m_ID = "",
                        QString m_Description = "", double m_Value = 0,
                        double m_Precision = 0, bool m_Tag = false);*/
        /**
         * @brief Constructor que inicializa un TModelParameter con valores proporcionados.
         * @param m_ID Identificación única para el parámetro.
         * @param m_Description Descripción del parámetro.
         * @param m_Value Valor numérico del parámetro.
         * @param m_Precision Precisión asociada al valor del parámetro.
         * @param m_Tag Etiqueta para marcar en caso de que queramos hacer un uso específico de ese parámetro.
         */
        TModelParameter(QString m_ID, QString m_Description, double m_Value,double m_Precision, bool m_Tag);

        /**
         * @brief Devuelve el índice del parámetro.
         * @return Índice del parámetro.
         */
        short int getIndex();
        //void setIndex(short int v_index);

        /**
         * @brief Devuelve la identificación única para el parámetro.
         * @return Identificación única para el parámetro.
         */
        QString getId();

        /**
         * @brief Establece la identificación única para el parámetro.
         * @param v_id Nueva identificación única para el parámetro.
         */
        void setid(QString v_id);

        /**
         * @brief Devuelve la descripción del parámetro.
         * @return Descripción del parámetro.
         */
        QString getDescription();

        /**
         * @brief Establece la descripción del parámetro.
         * @param v_description Nueva descripción del parámetro.
         */
        void setDescription(QString v_description);

        /**
         * @brief Devuelve el valor numérico del parámetro.
         * @return Valor numérico del parámetro.
         */
        double getValue();

        /**
         * @brief Establece el valor numérico del parámetro.
         * @param v_value Nuevo valor numérico del parámetro.
         */
        void setValue(double v_value);

        /**
         * @brief Devuelve la precisión asociada al valor del parámetro.
         * @return Precisión asociada al valor del parámetro.
         */
        double getPrecision();

        /**
         * @brief Establece la precisión asociada al valor del parámetro.
         * @param v_precision Nueva precisión asociada al valor del parámetro.
         */
        void setPrecision(double v_precision);

        /**
         * @brief Devuelve la etiqueta asociada al parámetro.
         * @return Etiqueta asociada al parámetro.
         */
        bool getTag();

        /**
         * @brief Establece la etiqueta asociada al parámetro.
         * @param v_tag Nueva etiqueta asociada al parámetro.
         */
        void setTag(bool v_tag);
};



// --------------------------------------------------------
//                    TModelReaction
// --------------------------------------------------------


class TModelReaction
{
    private:    // private members
        short int m_index;
        QString m_id;
        QString m_description;
        std::vector<int> m_reagent;
        std::vector<int> m_product;
        std::vector<int> m_parameter;
        QString m_equation;
        bool m_tag;

    public:     // constructors
        TModelReaction(short int v_Index = -1, QString v_ID = "",
                       QString v_Description = "", std::vector<int> v_Reagent= { 0 },
                       std::vector<int> v_Product = { 0 },
                       std::vector<int> v_Parameter= { 0 }, QString v_Equation= "",
                       bool v_Tag = false);

    public:     // getters/setters
        short int getIndex();
        void setIndex(short int v_index);
        QString getId();
        void setid(QString v_id);
        QString getDescription();
        void setDescription(QString v_description);
        std::vector<int> getAllReagents();
        void setAllReagents(std::vector<int> v_reagents);
        std::vector<int> getAllProducts();
        void setAllProducts(std::vector<int> v_products);
        std::vector<int> getAllParameters();
        void setAllParameters(std::vector<int> v_parameters);
        int GetReagentNo ();
        void SetReagentNo(std::vector<int>(int i));
        int GetProductNo ();
        void SetProductNo(std::vector<int>(int i));
        int GetOarameterNo ();
        void SetParameterNo(std::vector<int>(int i));
        QString getEquation();
        void setEquation(QString v_equation);
        bool getTag();
        void setTag(bool v_tag);

    public:     //public methods
        int ReagentsCount();
        int ProductsCount();
        int ParametersCount();
        TModelMetabolite &Reagent(const int index);
        TModelMetabolite &Product(const int index);
        TModelMetabolite &Parameter(const int index);

};


// --------------------------------------------------------
//                     TRunConfig
// --------------------------------------------------------


class TRunConfig
{
    private:    // private members
        double m_initTime;
        double m_endTime;
        size_t m_cycles;
        QString m_paramList;


    public:     // constructors
        TRunConfig(double v_initTime = 0, double v_endTime    = 0,
                   size_t v_cycles   = 0, QString v_paramList = ""):
                   m_initTime(v_initTime), m_endTime (v_endTime),
                   m_cycles (v_cycles), m_paramList (v_paramList){};

    public:     // getters/setters
        double getInitTime();
        void setInitTime(double t);
        double getEndTime();
        void setEndTime(double t);
        size_t getCycles();
        void setCycles(size_t value);
        QString getParamList();
        void setParamList(QString pList);


    public:     //public methods

};


// --------------------------------------------------------
//                     TFrameData
// --------------------------------------------------------


class TFrameData
{
private:    // private members

public:     // constructors

public:     // getters/setters

public:     //public methods

};


// --------------------------------------------------------
//                     TPathway
// --------------------------------------------------------


class TPathway
{
private:    // private members

public:     // constructors

public:     // getters/setters

public:     //public methods

};


