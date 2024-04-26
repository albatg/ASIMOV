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
        std::string* m_source;

    public:
        /**
         * @brief Constructor por defecto de la clase
         * @param v_source Apunta a nullptr por defecto.
         * @post Genera una instancia de la clase TRawInput con su contenido vacío.
        */
        TRawInput(std::string* v_source = nullptr);

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
        std::string getSource();

        /**
         * @brief Método que establece el valor de la fuente.
         * @param v_source Puntero a un objeto QString que se asignará como fuente.
         * @post El objeto m_source queda apuntando al objeto QString proporcionado.
        */
        void setSource(std::string& v_source);

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
 *@brief La clase TModelMetabolite implementa un tipo de dato para almacenar los
 *       metabolitos de una reacción y poder trabajar con ellos.
*/
class TModelMetabolite
{
private:    // private members
    /**
         * @brief s_metabolites Vector estático de la clase con todos los metabolitos creados.
         */
    static std::vector<TModelMetabolite> s_metabolites;
    /**
         * @brief Nombre largo del metabolito.
         */
    std::string m_name;

    /**
         * @brief Nombre corto del metabolito, es único.
         */
    std::string m_id;
    /**
         * @brief Índice numérico único del metabolito.
         */
    short int m_index;
    /**
         * @brief Valor inicial del metabolito.
         * @pre Toma el valor por defecto 0.
         */
    double m_initValue;

    /**
         * @brief Valor máximo que puede alcanzar el metabolito.
         * @pre Toma el valor por defecto INT_MAX,
         */
    double m_topValue;
    /**
         * @brief Valor mínimo que puede alcanzar el metabolito.
         * @pre Toma el valor por defecto 0.
         */
    double m_bottomValue;
    /**
         * @brief Valor actual del metabolito, comienza siendo m_initValue.
         */
    double m_value;
    /**
         * @brief Precisión asociada a los valores del metabolito.
         * @pre Toma el valor por defecto 0.0000001.
         */
    double m_precision;
    /**
         * @brief Etiqueta del metabolito.
         * @pre Toma el valor por defecto false.
         */
    bool m_tag;

public:
    /**
         * @brief TModelMetabolite Constructor de la clase, crea un objeto metabolito válido
         *        con los parámetros proporcionados.
         * @param m_index Índice numérico único del metabolito.
         * @param m_name Nombre largo del metabolito.
         * @param m_id Nombre corto del metabolito, único.
         * @param m_initValue Valor inicial del metabolito.
         * @param m_topValue Valor máximo que puede alcanzar el metabolito.
         * @param m_bottomValue Valor mínimo que puede alcanzar el metabolito.
         * @param m_value Valor actual del metabolito.
         * @param m_precision Precisión asociada al valor del metabolito.
         * @param m_tag Etiqueta asociada al metabolito.
         */
    TModelMetabolite(short int m_index, std::string m_name, std::string m_id, double m_initValue, double m_topValue,
                     double m_bottomValue, double m_value, double m_precision, bool m_tag);

    /**
         * @brief TModelMetabolite Constructor por defecto. Establece m_index = -1
         */
    TModelMetabolite();

    /**
         * @brief check Comprueba la consistencia de los datos recogidos del metabolito.
         * @return true si los datos son válidos, false en caso contrario.
         */
    bool check();

    // getters/setters
    /**
         * @brief getName devuelve el nombre largo del metabolito.
         * @return atributo m_name.
         */
    std::string getName();

    /**
         * @brief getId devuelve el nombre corto del metabolito.
         * @return atributo m_id.
         */
    std::string getId();

    /**
         * @brief getIndex devuelve el índice numérico asociado al metabolito.
         * @return atributo m_index.
         */
    short int getIndex();

    /**
         * @brief getInitValue devuelve el valor inicial del metabolito.
         * @return atributo m_initValue.
         */
    double getInitValue();

    /**
         * @brief getTopValue devuelve el valor máximo que puede alcanzar el metabolito.
         * @return atributo m_topValue.
         */
    double getTopValue();

    /**
         * @brief getBottomValue devuelve el valor mínimo que puede alcanzar el metabolito.
         * @return atributo m_bottomValue.
         */
    double getBottomValue();

    /**
         * @brief getValue devuelve el valor actual del metabolito.
         * @return atributo m_value.
         */
    double getValue();

    /**
         * @brief getPrecision devuelve la precisión asociada al metabolito.
         * @return atributo m_precision.
         */
    double getPrecision();

    /**
         * @brief getTag devuelve la etiqueta que tiene el metabolito.
         * @return atributo m_tag.
         */
    bool getTag();

    /**
         * @brief setValue modifica el valor actual del metabolito.
         * @param v_value nuevo valor del metabolito.
         */
    void setValue(double v_value);

    /**
         * @brief setTag modifica la etiqueta del metabolito.
         * @param v_tag nueva etiqueta.
         */
    void setTag(bool v_tag);

    /**
         * @brief range calcula el rango de valores del metabolito.
         * @return double resultante de restar (m_topValue - m_bottomValue).
         */
    double range();

    static std::vector<TModelMetabolite> getMetabolites(){
        return s_metabolites;
    }

    static void clear();

    friend class TProcess;
};
//=========================================================


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
          * @brief s_params Vector estático de la clase con todos los parámetros creados.
         */
        static std::vector<TModelParameter> s_params;
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
        std::string m_id;
        /**
         *@brief Decripción del parámetro.
        */
        std::string m_description;
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
        TModelParameter(std::string m_ID, std::string m_Description, double m_Value,double m_Precision, bool m_Tag);

        /**
         * @brief TModelParameter Constructor por defecto. Establece m_index = -1
         */
        TModelParameter();

        /**
         * @brief check Comprueba la consistencia de los datos recogidos del parámetro.
         * @return true si los datos son válidos, false en caso contrario.
         */
        bool check();

        /**
         * @brief Devuelve el índice del parámetro.
         * @return Índice del parámetro.
         */
        short int getIndex();

        /**
         * @brief Devuelve la identificación única para el parámetro.
         * @return Identificación única para el parámetro.
         */
        std::string getId();

        /**
         * @brief Establece la identificación única para el parámetro.
         * @param v_id Nueva identificación única para el parámetro.
         */
        void setid(std::string v_id);

        /**
         * @brief Devuelve la descripción del parámetro.
         * @return Descripción del parámetro.
         */
        std::string getDescription();

        /**
         * @brief Establece la descripción del parámetro.
         * @param v_description Nueva descripción del parámetro.
         */
        void setDescription(std::string v_description);

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

        static std::vector<TModelParameter> getParams(){
            return s_params;
        }

        static void clear();

        /**
         * @brief Clase amiga que puede acceder a los datos privados de TFormalism.
         */
        friend class TProcess;
};


// --------------------------------------------------------
//                    TFormalism
// --------------------------------------------------------

class TFormalism
{
private:
    /**
         * @brief s_formalisms Vector con todos los formalismos creados.
         *        Su posición en el vector coincide con su id.
         */
    static std::vector<TFormalism> s_formalisms;

    /**
         * @brief m_id Identificador del formalismo.
         */
    std::string m_id;

    /**
         * @brief m_name Nombre bioquímico del formalismo.
         */
    std::string m_name;

    /**
         * @brief m_formalism Cadena de caracteres que representa la ecuación del formalismo.
         */
    std::string m_formalism;

    /**
         * @brief m_variables Vector de nombres de variables que aparecen en el formalismo.
         */
    std::vector<std::string> m_variables;

public:
    /**
         * @brief TFormalism Constructor de la clase TFormalism. Crea un objeto formalismo válido.
         * @param m_id Identificador del formalismo.
         * @param m_name Nombre largo del formalismo.
         * @param m_formalism Ecuación del formalismo.
         * @param m_variables Vector de nombres de variables que aparecen en la ecuación.
         */
    TFormalism(std::string m_id, std::string m_name, std::string m_formalism, std::vector<std::string> m_variables);

    /**
         * @brief TFormalism Constructor por defecto. Establece m_id = "F", el vector m_variables queda vacío.
         */
    TFormalism();

    /**
         * @brief check Método que comprueba la consistencia entre las variables y la ecuación
         *        proporcionadas. En el formalismo deben aparecer todas las variables proporcionadas
         *        y sólo esas. Es llamado dentro del constructor antes de crear el objeto.
         * @return true si los datos del formalismo son correctos, false en caso contrario.
         */
    bool check();

    /**
         * @brief getId Devuelve el identificador del formalismo.
         * @return devuelve el QString m_id
         */
    std::string getId();

    /**
         * @brief getName Devuelve el nombre del formalismo.
         * @return devuelve el QString m_name
         */
    std::string getName();

    /**
         * @brief getFormalism Devuelve la ecuación del formalismo.
         * @return devuelve el QString m_formalism
         */
    std::string getFormalism();

    static std::vector<TFormalism> getFormalisms();

    /**
         * @brief getVariables Devuelve una lista de las variables que participan
         * @return devuelve un vector con los id de las variables
         */
    std::vector<std::string>& getVariables();

    static void clear();

    /**
         * @brief Clase amiga que puede acceder a los datos privados de TFormalism.
         */
    friend class TProcess;

};
//=========================================================


// --------------------------------------------------------
//                    TProcess
// --------------------------------------------------------

class TProcess
{
private:
    /**
         * @brief s_processes Vector con todos los procesos creados.
         *        Su posición en el vector coincide con su id.
         */
    static std::vector<TProcess> s_processes;

    /**
         * @brief m_id Identificador del proceso.
         */
    std::string m_id;

    /**
         * @brief m_name Nombre corto del proceso.
         */
    std::string m_name;

    /**
         * @brief m_description Nombre bioquímico del proceso.
         */
    std::string m_description;

    /**
         * @brief m_idForm Identificador del formalismo al que hace referencia.
         */
    std::string m_idForm;

    /**
         * @brief m_substances Vector de identificadores de las sustancias (metanodos y parámetros)
         *        que aparecen en el proceso.
         */
    std::vector<std::string> m_substances;

public:

    /**
         * @brief TProcess Constructor de la clase TProcess. Crea un proceso válido.
         * @param m_id Identificador del proceso.
         * @param m_name Nombre corto del proceso.
         * @param m_description Nombre bioquímico del proceso.
         * @param m_idForm Identificador del formalismo que usa.
         * @param m_substances Vector de las sustancias que aparecen en el proceso.
         */
    TProcess(std::string m_id, std::string m_name, std::string m_description, std::string m_idForm, std::vector<std::string> m_substances);

    /**
         * @brief TProcess Constructor por defecto. Establece m_id = "P", el vector m_sbustances queda vacío.
         */
    TProcess();

    /**
         * @brief getId Devuelve el id del proceso
         * @return QString
         */
    std::string getId();

    /**
         * @brief getName Devuelve el nombre corto del proceso
         * @return QString
         */
    std::string getName();

    /**
         * @brief getDescription Devuelve el nombre largo del proceso
         * @return QString
         */
    std::string getDescription();

    /**
         * @brief getIDForm Devuelve el id del formalismo asociado al proceso
         * @return QString
         */
    std::string getIDForm();

    /**
         * @brief getSubstances Devuelve por referencia un vector con los id de las sustancias que
         *        participan en el proceso
         * @return vector de QString con los id de las sustancias
         */
    std::vector<std::string>& getSubstances();

    /**
         * @brief check Método que comprueba la consistencia de los datos del proceso recogidos.
         *        El formalismo y las variables (metanodos y parámetros) recogidas deben existir.
         *        Se llama dentro del constructor, para crear un objeto Proceso válido.
         * @return true si los datos del proceso son correctos, false en caso contrario.
         */
    bool check();

    /**
         * @brief getFormalism Método que devuelve el objeto formalismo asociado al proceso.
         * @param QString Identificador del formalismo asociado al proceso.
         * @return Objeto TFormalismo asociado al proceso.
         */
    TFormalism getFormalism(std::string m_idForm);

    /**
         * @brief getProcess Método que construye la ecuación del proceso basada en el formalismo y las
         *        variables del objeto Proceso que lo llama.
         * @return Cadena de caracteres con la ecuación del proceso, donde las variables son las especificadas.
         */
    std::string getProcess();

   static void clear();

    static std::vector<TProcess> getProcesses();
};

class TEquation
{
private:
    /**
        * @brief Vector con todos las ecuaciones.
        *        Su posición en el vector coincide con su id.
    */
    static std::vector<TEquation> s_equations;

    /**
        * @brief Index de la ecuación.
    */
    int m_index;

    /**
        * @brief Ecuación diferencial que forma parte del proceso a estudiar.
    */
    std::string m_equation;

    std::string m_variable;

    /**
        * @brief  Vector de identificadores de los procesos que aparecen en la ecuación.
    */
    std::string m_expression;

public:

    /**
         * @brief Constructor de la clase TEcuation.
         * @param m_id Identificador de la ecuación.
         * @param m_ecuation Ecuación diferencial de uno o varios procesos
         * @param m_variable Variable que participa en la ecuacion
         * @param m_processes Vector de ecuaciones.
         */
    TEquation(int m_index, std::string m_equation, std::string m_variable,  std::string m_expression);

    /**
         * @brief TEquation Constructor por defecto. Establece m_id = "E";
         */
    TEquation();

    /**
         * @brief  Devuelve el index de la ecuacion
         * @return std::string
         */
    int getIndex();

    /**
         * @brief  Devuelve un string con la expresión de la ecuación diferencial
         * @return std::string
         */
    std::string getEquation();

    /**
         * @brief  Devuelve un string con la expresión de los procesos que participan en la ecuación
         * @return std::string
         */

    std::string getVariable();

    std::string getExpression();

    /**
         * @brief check Método que comprueba la consistencia de los datos de la ecuación.
         * @return true si los datos del proceso son correctos, false en caso contrario.
         */
    bool check();

    TProcess getProcess(std::string m_IdProc);

    std::vector<std::string> getSplittedExpression(std::string expression);

    std::string getEquationChanged();

    static void clear();

    static std::vector<TEquation> getEquations();
};

//=========================================================


// --------------------------------------------------------
//                    TModelReaction
// --------------------------------------------------------

/**
 * @brief La clase TModelReaction encapsula la información necesaria
 *        para gestionar una reacción metabólica.
 */

class TModelReaction
{
private:    // private members

    /**
         * @brief s_counter Contador numérico del número de reacciones almacenadas.
         *        Se actualiza en el constructor de la clase, sumando uno con cada
         *        reacción creada.
         */
    static short int s_counter;

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
    std::string m_paramList;


public:     // constructors
    TRunConfig(double v_initTime = 0, double v_endTime    = 0,
               size_t v_cycles   = 0, std::string v_paramList = ""):
        m_initTime(v_initTime), m_endTime (v_endTime),
        m_cycles (v_cycles), m_paramList (v_paramList){};

public:     // getters/setters
    double getInitTime();
    void setInitTime(double t);
    double getEndTime();
    void setEndTime(double t);
    size_t getCycles();
    void setCycles(size_t value);
    std::string getParamList();
    void setParamList(std::string pList);


public:     //public methods

};

#endif // ASIMOV_LIBRARY_H

