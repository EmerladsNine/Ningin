using Microsoft.VisualStudio.Text.Classification;
using Microsoft.VisualStudio.Utilities;
using System.ComponentModel.Composition;

namespace NinginToolsExtension
{
    /// <summary>
    /// Classification type definition export for NinginScene
    /// </summary>
    internal static class NinginSceneClassificationDefinition
    {

        // This disables "The field is never used" compiler's warning. Justification: the field is used by MEF.
#pragma warning disable 169

        /// <summary>
        /// Defines the "NinginScene" classification type.
        /// </summary>
        [Export(typeof(ClassificationTypeDefinition))]
        [Name("NinginScene")]
        private static ClassificationTypeDefinition typeDefinition;

#pragma warning restore 169

        [Export(typeof(ClassificationTypeDefinition))]
        [Name("NinginSceneKeyword")]
        internal static ClassificationTypeDefinition NinginSceneKeywordType = null;

        [Export(typeof(ClassificationTypeDefinition))]
        [Name("NinginSceneComment")]
        internal static ClassificationTypeDefinition NinginSceneCommentType = null;

    }
}
