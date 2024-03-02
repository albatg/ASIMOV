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
 *@brief Definición de la clase TRawInput que implementa un tipo de dato
 *       para poder gestionar los archivos de entrada del programa.
*/
class TRawInput
{
    private:    // private members
        /**
         * @brief Variable booleana que indica si se ha cargado un archivo.
        */
        bool m_loaded;
        /**
         * @brief Variable de tipo QString en el que se guardará el contenido del archivo.
        */
        QString* m_source;

    public:
        /**
         * @brief Constructor por defecto de la clase.
         * @param v_source Apunta a nullptr por defecto.
         * @post Genera una instancia de la clase TRawInput con su contenido vacío.
        */
        TRawInput(QString* v_source = nullptr);

        /**
         * @brief Destructor de instancias de tipo TRawInput.
         *
        */
        ~TRawInput();

        //getters/setters
        /**
         * @brief Método que devuelve el contenido de una fuente.
         * @return Devuelve un QString que se corresponde con el valor de la fuente.
        */
        QString getSource();

        /**
         * @brief Método que establece el valor de la fuente.
         * @param v_source Puntero a un objeto QString que se asignará como fuente.
         * @post El objeto m_source queda apuntando al objeto QString proporcionado.
        */
        void setSource(QString* v_source);

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
        void newRawInput();
        unsigned short verifyModel();
        bool createModel(TPathway& v_model);
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
         * @brief Nombre largo del metabolito.
         */
        QString m_name;

        /**
         * @brief Nombre corto del metabolito, es único.
         */
        QString m_id;

        /**
         * @brief Índice numérico y único para cada metabolito.
         * @post Todos los metabolitos procesados deben tener índices correlativos.
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
         * @brief TModelMetabolite constructor de la clase, crea un objeto metabolito válido
         *        con los parámetros proporcionados.
         * @param m_name nombre largo del metabolito.
         * @param m_id nombre corto del metabolito, único.
         * @param m_index índice numérico único asociado al metabolito.
         * @param m_initValue valor inicial del metabolito.
         * @param m_topValue valor máximo que puede alcanzar el metabolito.
         * @param m_bottomValue valor mínimo que puede alcanzar el metabolito.
         * @param m_value valor actual del metabolito.
         * @param m_precision precisión asociada al valor del metabolito.
         * @param m_tag etiqueta asociada al metabolito.
         */
        TModelMetabolite(QString m_name, QString m_id, short int m_index, double m_initValue, double m_topValue,
                         double m_bottomValue, double m_value, double m_precision, bool m_tag);

        // getters/setters
        /**
         * @brief getName devuelve el nombre largo del metabolito.
         * @return atributo m_name.
         */
        QString getName();

        /**
         * @brief getId devuelve el nombre corto del metabolito.
         * @return atributo m_id.
         */
        QString getId();

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
         * @brief TModelParameter constructor de la clase, crea un objeto parámetro válido.
         * @param m_ID nombre corto del parámetro, es único.
         * @param m_Description nombre largo del parámetro.
         * @param m_Value valor actual del parámetro.
         * @param m_Precision precisión asociada al parámetro.
         * @param m_Tag etiqueta asociada al parámetro.
         */
        TModelParameter(QString m_ID, QString m_Description, double m_Value,double m_Precision, bool m_Tag);

        /**
         * @brief getIndex devuelve el índice numérico del parámetro.
         * @return variable estática s_counter.
         */
        short int getIndex();

        /**
         * @brief getId devuelve el nombre corto del parámetro.
         * @return atributo m_id.
         */
        QString getId();

        /**
         * @brief getDescription devuelve el nombre largo del parámetro.
         * @return atributo m_description.
         */
        QString getDescription();

        /**
         * @brief getValue devuelve el valor actual del parámetro.
         * @return atributo m_value.
         */
        double getValue();

        /**
         * @brief setValue modifica el valor actual del parámetro.
         * @param v_value valor nuevo del parámetro.
         */
        void setValue(double v_value);

        /**
         * @brief getPrecision devuelve la precisión asociada al parámetro.
         * @return atributo m_precision.
         */
        double getPrecision();

        /**
         * @brief getTag devuelve la etiqueta asociada al parámetro.
         * @return atributo m_tag.
         */
        bool getTag();
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


